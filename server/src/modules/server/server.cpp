#include "server.hpp"

/**
   @brief 设置非阻塞文件描述符
   @param fd
   @return
*/
int setnoblocking (int fd) {
  int old_option = fcntl (fd, F_GETFL);
  int new_option = old_option |= O_NONBLOCK;
  fcntl (fd, F_SETFL, new_option);
  return old_option;
}

/**
   @brief 初始化服务端套接字
   @param ip
   @param port
   @return new server socket
*/
int Server::Init (const char* ip, const int port) {
  std::cout << "IP: " << GREEN  << ip << RESET << std::endl;
  std::cout << "PORT: " << GREEN  << port << RESET << std::endl;
  int sock;
  int ret;
  
  sock = socket (AF_INET, SOCK_STREAM, 0);
  bzero (&server_addr, sizeof (server_addr));
  
  inet_pton (AF_INET, ip, &server_addr.sin_addr.s_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons (port);
  if (sock <= 0 ) {
    perror ( "create socket"); return sock;
  }
  ret = bind (sock, (sockaddr*)&server_addr, sizeof (server_addr));
  if (ret == -1) {
    perror ("bind socket"); return -1;
  }
  ret = listen (sock, 120);
  if (ret == -1) {
    perror ("listen socket"); return -1;
  }
  return sock;
}

void add_fd (int epoll_fd, int sock_fd) {
  epoll_event event;
  event.data.fd =  sock_fd;
  event.events = EPOLLIN;
  event.events |= EPOLLET;
  epoll_ctl (epoll_fd, EPOLL_CTL_ADD, sock_fd, &event);
  setnoblocking (sock_fd);
}

void Server::EventWith (int epoll_fd, int number, int listen_fd,
                        epoll_event* events) {
  for (int i = 0; i < number; i++) {
    int sock_fd = events[i].data.fd;
    
    // 当事件来自server_fd 时，说明有新的用户发起连接
    if (sock_fd == listen_fd) {
      struct sockaddr_in client_addr;
      socklen_t socklen = sizeof (client_addr);
      int connect_fd = accept (listen_fd, (sockaddr*)&client_addr, &socklen);
      add_fd (epoll_fd, connect_fd);
    }
    // 如果不是server_fd 触发事件，则说明connect_fd 发生可读或可写事件
    else if (events[i].events & EPOLLIN) {
      std::string result_str = ResultMessageString (sock_fd);
      std::cout << GREEN << result_str << std::endl;
      SmallMessageProcess (result_str, sock_fd);
    } else {
      std::cout << BOLDBLACK << "其他事情发生" << RESET << std::endl;
    }
  }
}

// 处理客户端发送的消息
std::string  Server::ResultMessageString (int sock_fd)  {
  char buf[BUFSIZ];
  std::string message;
  while (1) {
    memset (buf, '\0', BUFSIZ);
    int ret = recv (sock_fd, buf, BUFSIZ - 1, 0);
    if (ret < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        std::cout << RED << "数据读取完毕" << RESET << "\n\n\n";
        return message;
      }
      close (sock_fd);
      break;
    } else if (ret == 0) {
      std::cout << CYAN << sock_fd << " 客户端关闭连接 " << RESET << std::endl;
      close (sock_fd);
    } else {
      message += buf;
    }
  }
  return message;
}

// 处理客户端请求
void Server::SmallMessageProcess (std::string response, int sock)  {
  nl_json body;
  
  try {
    body = nl_json::parse (response);
  } catch (nl_json::parse_error) {
    pool->Submit (SendMessage, RESULT_ERROR_MESSAGE, sock);
  }
  std::cout << YELLOW << body.dump (4) << RESET << std::endl;
  if (not body.contains ("message_type")) {
    pool->Submit (SendMessage, RESULT_ERROR_MESSAGE, sock);
  }
  const std::string message_type = body["message_type"];
  // 检查类型是否正确
  if (MessageTypeValue.find (message_type) == MessageTypeValue.end()) {
    pool->Submit (SendMessage, RESULT_ERROR_MESSAGE, sock);
    std::cout << "类型不正确" << std::endl;
    return;
  }
  MessageType type =  MessageTypeValue.at (message_type);
  switch (type) {
    case MessageType::login: { // 登陆
      std::cout << GREEN << "客户端请求登陆" << RESET << std::endl;
      std::string message = ResultLoginString (body);
      std::cout << GREEN << "---- show res message\n";
      std::cout << message << std::endl;
      std::cout  << "---- end res message" << RESET << std::endl;
      pool->Submit (SendMessage, message, sock);
      break;
    }
    case MessageType::registered: { // 注册
      std::string message = ResultRegisteredString (body);
      pool->Submit (SendMessage, message, sock);
      break;
    }
    case MessageType::videocall: { // 视频电话
      break;
    }
    case MessageType::text: { // 文本消息
      int clinet_sock;
      std::string message = ResultTextString (body, clinet_sock);
      pool->Submit (SendMessage, message, clinet_sock);
      break;
    }
    case MessageType::call: { // 电话
      break;
    }
    case MessageType::voice: { // 语音
      break;
    }
    default: break;
  }
}

/**
   @brief 处理用户发送的登陆请求头，返回响应头字符串
   @param header
   @return
*/
std::string Server::ResultLoginString (const nl_json body)  {
  if (not body.contains ("user_account") or not body.contains ("user_password")) {
    std::cout << "查询失败" << std::endl;
    return RESULT_ERROR_MESSAGE;
  }
  std::string user_account = body["user_account"];
  std::string user_password = body["user_password"];
  MYSQL_RES* res =
    dataSchema.Query ("select * from m_base.User where user_account = " +
                      user_account +
                      " and user_password='" +
                      user_password + "';" );
  std::cout << "查询到" << dataSchema.CountQuery (res) << "条数据" <<
            std::endl;
            
  if (dataSchema.CountQuery (res) == 1) {
    std::cout <<  "登陆成功"  << std::endl;
    nl_json obj = {
      {"message_type", MESSAGE_LOGIN},
      {"status", true}
    };
    return obj.dump();
  }
  return RESULT_ERROR_MESSAGE;
}

/**
   @brief 处理用户注册发送的请求头，返回相应头字符串
   @param header
   @return
*/
std::string Server::ResultRegisteredString (const nl_json body)  {
  return RESULT_ERROR_MESSAGE;
}

/**
   @brief 处理用户请求发送文本消息相应头，返回响应的字符串
   @param header
   @param client_sock
   @return
*/
std::string Server::ResultTextString (const nl_json body, int& client_sock)  {
  return std::string();
}
