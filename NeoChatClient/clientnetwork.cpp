#include "clientnetwork.h"

ClientNetWork::ClientNetWork(QObject *parent)
    : QObject{parent}
{

}

ClientNetWork *ClientNetWork::getInstance()
{
    static ClientNetWork * obj;
    obj = new ClientNetWork();
    return obj;
}
