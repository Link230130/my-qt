#ifndef MYTCPTHREAD_H
#define MYTCPTHREAD_H

#include <QThread>
#include <QTcpSocket>

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

class MyTcpThread : public QThread
{
    Q_OBJECT
public:
    explicit MyTcpThread(qintptr flag);
    ~MyTcpThread();
protected:
    void run() override;

signals:

public slots:


private:
    qintptr socketDescriptor;
    QTcpSocket* socket;
    CustomData data;
};

#endif // MYTCPTHREAD_H
