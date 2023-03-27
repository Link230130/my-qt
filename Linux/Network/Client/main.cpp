#include <iostream>
#include "unistd.h"
#include "arpa/inet.h"
#include <string>
#include <cstring>

using namespace std;

int main()
{
    //1.创建用于通信的套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        cout << "socket" << endl;
    }
    //2.连接服务器
    sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);
    int ret = connect(fd, (sockaddr*)&saddr, sizeof(saddr));
    if (ret == -1) {
        cout << "connect error" << endl;
    }

    //3.套接字通信
    std::string sendMsg = "";
    char recvMsg[1024];
    int number = 0;
    while (1)
    {
        //发送数据
        sendMsg = ("hello, i am client");
        cout << "client will send msg to server, msg=" << sendMsg << endl;
        send(fd, sendMsg.c_str(), sendMsg.length()+1, 0);
        //接收数据
        memset(recvMsg, 0, sizeof(recvMsg));
        int len = recv(fd, recvMsg, sizeof(recvMsg), 0);
        if (len > 0) {
            cout << "server say : " << recvMsg << endl;
        }
        else if (len == 0) {
            cout << "disconnect and break" << endl;
            break;
        }
        else {
            cout << "recv error" << endl;
            break;
        }
        sleep(1);
    }
    close(fd);
    return 0;
}