#pragma once
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QObject>
#include <QDebug>
#include <regex>
#include <iostream>

class NetWork: public QObject {
    Q_OBJECT
  public:
    NetWork (QObject* parent);
    NetWork (QString ip, int port, QObject* parent);
    ~NetWork();
    // init connection server
    void InitServer (QString ip, int port);
    // send message to server
    void SendMessage (const QByteArray& message);
    void SendMessage (const QMap<QString, QString>& message);
    // read server message
    void RecvMessage (QByteArray& message);
  signals:
    void is_connected (bool); // send connection status signal
    void newMessage (); // server send message to client signal
    // send message to server error signal
    void SendMessageError (QString error_str);
  private:
    QTcpSocket socket;
};

using Map = std::unordered_map<std::string, std::string>;
Map parseMessageRequestHeaders (std::string httpResponse);
void ShowMessageHeader (Map header);
