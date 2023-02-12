#include "mytcpserver.h"
#include "mytcpthread.h"
MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer(parent)
{

}

MyTcpServer::~MyTcpServer()
{
    MyTcpThread* tcp= nullptr;
    QList<MyTcpThread*>::iterator it = listTcp.end();
    while (it != listTcp.begin()) {
        tcp = (*it);
        it--;
        delete tcp;
    }
}

void MyTcpServer::incomingConnection(qintptr handle)
{
    qDebug() << "newConnection..." << ", handle=" << handle;
    MyTcpThread* newTcp = new MyTcpThread(handle);
    listTcp.append(newTcp);
    newTcp->start();
}
