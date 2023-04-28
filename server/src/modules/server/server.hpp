#pragma once
#include <iostream>
#include <sys/epoll.h>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstdio>
#include <map>
#include <tasks/tasks.hpp>
#include "Message/MessageProcessor.hpp"
#include <user/user.hpp>
#include <unordered_map>
#include <database/database.hpp>
#include "colorcout/colorcout.hpp"
#include "./response.hpp"
#define MAX_EVENTS_NUMBER 1024

class Server {
  public:
    Server (ThreadPool* pool): pool (pool) {
      ReConf conf (CONFIGPATH);
      dataSchema.Connect (conf);
    };
    ~Server() {};
    int Init (const char* ip, const int port);
    void EventWith (int epoll_fd, int number, int  listen_fd, epoll_event* event);
  private:
    std::string ResultMessageString (int socket);
    void SmallMessageProcess (Map header, int sock);
    // Processing login response
    std::string ResultLoginString (const Map header);
    // Processing registration response
    std::string ResultRegisteredString (const Map header);
    // Processing text response
    std::string ResultTextString (const Map header, int& client_sock);
  private:
    std::unordered_map<std::string, User> user_map; // 用户列表
    char* ip;               // ip地址
    int port;               // 端口
    struct sockaddr_in server_addr; // server socket 结构体
    std::map<std::string, User> UserMap;
    ThreadPool* pool;
    DataSchema dataSchema;
};

int setnoblocking (int fd);
void add_fd (int epoll_fd, int sock_fd);
