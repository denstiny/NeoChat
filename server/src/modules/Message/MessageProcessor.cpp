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
  //close (sock);
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
