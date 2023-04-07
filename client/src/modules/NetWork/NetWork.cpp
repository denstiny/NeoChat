#include "NetWork.hpp"

NetWork::NetWork (QObject* parent): QObject (parent)  {

}
NetWork::NetWork (QString ip, int port, QObject* parent = nullptr):
  QObject (parent)  {
  InitServer (ip, port);
}

/**
   @brief 初始化socket 连接server
   @param ip 服务器ip地址
   @param port 服务器端口
*/
void NetWork::InitServer (QString ip, int port)  {
  socket.connectToHost (ip, port);
  connect (&socket, &QTcpSocket::connected, [this]() {
    emit is_connected (true);
  });
  connect (&socket, &QAbstractSocket::errorOccurred, [this]() {
    emit is_connected (false);
  });
  connect (&socket, &QIODevice::readyRead, [this]() {
    emit newMessage ();
  });
}

NetWork:: ~NetWork() {
  socket.close();
}

/**
   @brief 发送消息给服务器
   @param message
*/
void NetWork::SendMessage (const QByteArray& message)  {
  qint64 byteswriten = 0;
  qint64 totalbytes = message.size();
  qint64 wirtelen = 0;
  while (byteswriten < totalbytes) {
    wirtelen = socket.write (message.mid (0, totalbytes));
    if (wirtelen == -1) {
      emit SendMessageError ("Error: send message to server"); break;
    }
    if (not socket.waitForBytesWritten (10000)) {
      emit SendMessageError ("Failure: send message out time"); break;
    }
    byteswriten += wirtelen;
  }
}

/**
   @brief 读取接收到的新消息
   @param message
*/
void NetWork::RecvMessage (QByteArray& message)  {
  message.clear();
  message = socket.readAll();
}

// 发送消息给服务端
void NetWork::SendMessage (const QMap<QString, QString>& message)  {
  QString messageString;
  QMap<QString, QString>::const_iterator m_iter = message.begin();
  for (; m_iter != message.end(); m_iter ++) {
    messageString += m_iter.key() + ": " + m_iter.value() + "\r\n";
  }
  messageString += "\r\n";
  if (messageString.size() != 0) {
    SendMessage (messageString.toUtf8());
  }
}

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


void ShowMessageHeader (Map header)  {
  Map::const_iterator header_iterator = header.begin();
  std::cout  << " ---- show message header"  << std::endl;
  for (; header_iterator != header.end(); header_iterator ++ ) {
    std::cout << "key: "
              << header_iterator->first
              << " value: "
              << header_iterator->second
              << std::endl;
  }
  std::cout << " ---- end message header"  << std::endl;
}
