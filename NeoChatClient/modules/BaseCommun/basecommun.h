#ifndef BASECOMMUN_H
#define BASECOMMUN_H
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>
#include <regex>
#include <iostream>



class BaseCommun : public QObject
{
    Q_OBJECT
public:
    explicit BaseCommun(QObject *parent = nullptr);
    ~BaseCommun();
    Q_INVOKABLE void InitServer (QString ip, int port);
    // send message to server
    Q_INVOKABLE void SendMessage (const QString& message);
    //Q_INVOKABLE void SendMessage (const QMap<QString, QString>& message);
    QString RecvMessage ();

    QString getIp() const;
    void setIp(const QString &newIp);

    int getPort() const;
    void setPort(const int &newPort);

signals:
    void is_connected (bool status); // send connection status signal
    void newMessage (QString message); // server send message to client signal
    // send message to server error signal
    void SendMessageError (QString error_str);
    void start(bool status);

    void ipChanged();
    void portChanged();

private:
    QTcpSocket socket;
    QString ip;
    int port;
    Q_PROPERTY(QString ip READ getIp WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)
};

using Map = std::unordered_map<std::string, std::string>;
Map parseMessageRequestHeaders (std::string httpResponse);
void ShowMessageHeader (Map header);

#endif // BASECOMMUN_H
