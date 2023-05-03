#include "MessageProcessor.hpp"
#include "colorcout/colorcout.hpp"

// 解析 消息相应头
Map parseMessageRequestHeaders (std::string httpResponse)  {
  Map header;
  std::regex headerFieldRegex (R"((.+): (.+))");
  std::smatch headerFieldMatch;
  size_t headerEnd = httpResponse.find ("\r\n\r\n");
  if (headerEnd != std::string::npos) {
    std::string headerSection = httpResponse.substr (0, headerEnd);
    std::string::const_iterator headerStart = headerSection.cbegin();
    while (std::regex_search (headerStart, headerSection.cend(), headerFieldMatch,
                              headerFieldRegex)) {
      std::string headerField = headerFieldMatch[1].str();
      std::string headerValue = headerFieldMatch[2].str();
      header[headerField] = headerValue;
      headerStart = headerFieldMatch.suffix().first;
    }
  }
  return header;
}

// 解析请求内容
nlohmann::json parseMessageRequestBody (std::string response) {
  nlohmann::json body;
  size_t bodyStart =  response.find ("\r\n\r\n");
  if (bodyStart != std::string::npos) {
    std::string body_str = response.substr (bodyStart + 4);
    try {
      body = nlohmann::json::parse (body_str);
    } catch (nlohmann::json::parse_error) {
      body = {};
    }
  }
  return body;
}

void SendMessage (std::string message, int sock)  {
  std::cout << "发送消息给客户端" << std::endl;
  size_t len = message.size();
  size_t bytes = 0;
  while (len > 0) {
    bytes = send (sock, message.c_str(), message.size(), 0);
    if (bytes == -1) {
      return;
    }
    len -= bytes;
  }
  
  std::cout << "消息发送完毕" << std::endl;
  // 响应完成之后关闭客户端
  close (sock);
}

void ShowMessageHeader (Map header)  {
  Map::const_iterator header_iterator = header.begin();
  std::cout << RED << " ---- show message header" << RESET << std::endl;
  for (; header_iterator != header.end(); header_iterator ++ ) {
    std::cout << GREEN
              << "key: "
              << header_iterator->first
              << " value: "
              << header_iterator->second << RESET
              << std::endl;
  }
  std::cout << RED << " ---- end message header" << RESET << std::endl;
}

void ShowMessageBody (nlohmann::json json) {
  std::cout << RED << " ---- show message body" << RESET << std::endl;
  std::cout << GREEN << json.dump (4) << RESET;
  std::cout << RED << " ---- end message body" << RESET << std::endl;
}


const std::string Message::getMessageId()  {
  return getHeaderVaue ("MessageId");
}

const std::string Message::getHeaderVaue (std::string key)  {
  if (header.count (key) == 0) {
    return std::string();
  }
  return header[key];
}

const std::string Message::getMessageLength()  {
  return getHeaderVaue ("MessageLength");
}

const std::string Message::getMessageTotalLength()  {
  return getHeaderVaue ("TotalLength");
}

const nlohmann::json Message::getBody()  {
  return body;
}

void Message::parseMessage (std::string response)  {
  header = parseMessageRequestHeaders (response);
  body = parseMessageRequestBody (response);
}

void Message::showMessage()  {
  ShowMessageHeader (header);
  ShowMessageBody (body);
}
