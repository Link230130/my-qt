#include <QApplication>

#include <QTime>
#include <QTcpSocket>
#include <QHostAddress>

/*
与MyTcpServer进行通信的客户端
*/

void wait(unsigned int T)
{
    QTime time;
    time.start();
    while ((unsigned int)time.elapsed() < T) {
        QCoreApplication::processEvents();
    }
}

struct CustomData
{
    CustomData() {
        memset(data1,0,sizeof(char)*10);
        memset(&data2,0,sizeof(int));
        memset(&data3,0,sizeof(float));
    }
    char data1[10];
    int data2;
    float data3;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost(QHostAddress("127.0.0.1"),49999);
    qDebug() << "try to connect...";
    if(socket.waitForConnected(5000))
    {
        qDebug() << "connect sucessfully! ";
    }else
    {
        qDebug() << "connect failed!";
        socket.close();
        return a.exec();
    }
    CustomData data;
    char arr[10] = {100};
    memcpy(&(data.data1),&arr,sizeof(char)*10);
    data.data2 = 99;
    data.data3 = 11.1f;
    int count = 0;
    while (socket.state() && QAbstractSocket::ConnectedState) {
        socket.write((char*)(&data),sizeof(CustomData));
        //发送等待，如果发送出第一个字符，则立即返回true,否则超时后返回false
        socket.waitForBytesWritten();
        qDebug() << QString("send data sucess, count = %1 ").arg(++count);
        //等待三秒后再次发送数据
        wait(10000);
    }

    return a.exec();
}
