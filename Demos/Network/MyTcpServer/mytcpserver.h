#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QList>

class MyTcpThread;

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

protected:
    void incomingConnection(qintptr handle) override;

signals:

public slots:

private:
    QList<MyTcpThread*> listTcp;
};

#endif // MYTCPSERVER_H
