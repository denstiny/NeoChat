#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QDebug>
#include <QtQml>

class ClientNetWork : public QObject
{
    // TODO: 实现与服务器通信的类
    Q_OBJECT
public:
    explicit ClientNetWork(QObject *parent = nullptr);
    static ClientNetWork * getInstance();
private:
    QTcpSocket socket;
signals:

};

#endif // CLIENTNETWORK_H
