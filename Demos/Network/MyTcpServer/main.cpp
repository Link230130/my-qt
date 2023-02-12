#include <QCoreApplication>
#include <QTime>
#include <QDebug>
#include "mytcpserver.h"

#define RUNTIME 60*60*1000
//#define RUNTIME 3*1000

/*
实现了一个简易的TcpServer服务端，QTcpServer只支持一个客户端的连接
    支持多个MyTcpClient客户端进行传输自定义二进制数据
    （暂时未处理如客户端数量限制，内存回收等细节）
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "MyTcpServer start!!!";
    QTime time;
    time.start();

    MyTcpServer server;
    server.listen(QHostAddress::Any,49999);

    while ((unsigned int)time.elapsed() < (RUNTIME)) {
        QCoreApplication::processEvents();
    }

    server.close();
    qDebug() << "MyTcpServer close";

    return a.exec();
}
