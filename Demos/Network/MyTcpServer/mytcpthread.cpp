
#include "mytcpthread.h"
#include <QHostAddress>
MyTcpThread::MyTcpThread(qintptr flag)
    : QThread()
    ,socket(nullptr)
    ,socketDescriptor(flag)
{
    qDebug() << "new MyTcpThread, handle=" << flag;
}

MyTcpThread::~MyTcpThread()
{
    qDebug() << "destroy MyTcpThread, handle=" << socketDescriptor;
    if(socket != nullptr)
    {
        socket->close();
        delete socket;
    }
}

void MyTcpThread::run()
{
    qDebug() << "MyTcpThread runing, handle = " << socketDescriptor;
    if(socket != nullptr)
    {
        delete socket;
        socket = nullptr;
    }
    QString log;
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    //连接建立满足循环
    while (socket->state() && QAbstractSocket::ConnectedState) {
        //qDebug() << "socket->state()=" << socket->state();
        //如果有新数据可读，则立即返回true；如果发生错误或者超时返回false
        if(socket->waitForReadyRead(1000))
        {
            //先清空数据
            memset(&data,0,sizeof(CustomData));
            //接收一个自定义的结构体数据
            socket->read((char*)&data,sizeof(CustomData));
            //显示到控制台
            QString ip = QString(socket->peerAddress().toString());
            log = QString("rev data from %1 , data1= %2 , data2= %3 , data3= %4")
                    .arg(ip)
                    .arg(data.data1)
                    .arg(data.data2)
                    .arg(data.data3);
            qDebug() << log;
        }
    }
    qDebug() << "MyTcpThread run finished, handle = " << socketDescriptor;
}
