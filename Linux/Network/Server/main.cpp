#include <iostream>
#include "unistd.h"
#include "arpa/inet.h"
#include <string>
#include "pthread.h"

using namespace std;

#define IS_DEBUG 1

int main() {
    //1.创建监听的套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
#if IS_DEBUG
    cout << "socket succeed!!! and fd=" << fd << endl;
#endif
    if (fd == -1)
    {
        cout << "socket" << endl;
        return -1;
    }
    //2.绑定本地的IP 、Port
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if (ret == -1) {
        cout << "bind" << endl;
        return -1;
    }
#if IS_DEBUG
    cout << "bind succeed!!! and ret=" << ret << endl;
#endif
    //3.设置监听
    ret = listen(fd, 128);
    if (ret == -1) {
        cout << "listen error" << endl;
        return -1;
    }
#if IS_DEBUG
    cout << "listen succeed!!! and ret=" << ret << endl;
#endif
    //4.阻塞并等待客户端的连接
    struct sockaddr_in caddr;
    int addrLen = sizeof(caddr);

    while (1) {
        int cfd = accept(fd, (struct sockaddr*)&caddr, (socklen_t*)&addrLen);
        if (cfd == -1)
        {
            cout << "accept error and continue" << endl;
            continue;
        }
#if IS_DEBUG
        cout << "accept succeed!!! and cfd=" << cfd << endl;
#endif

        //创建子线程进行处理
        pthread_t tid;
        pthread_create(&tid, NULL, working, NULL);
        //分离子线程
        pthread_detach(tid);
    }
    close(fd);
}

//负责与客户端进行通信
void* working(void* arg) {

    //连接建立成功，打印客户端的IP和Port信息
    char ip[32];
    cout << "The client IP: " << inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)) << endl;
    cout << "The client Port: " << ntohs(caddr.sin_port) << endl;

    //5.与客户端通信
    while (1)
    {
        char buff[1024];
        int len = recv(cfd, buff, sizeof(buff), 0);
        if (len > 0)
        {
            cout << "client say: " << buff << endl;
            send(cfd, buff, len, 0);
        }
        else if (len == 0)
        {
            cout << "buff is 0" << endl;
            break;
        }
        else {
            cout << "recv error" << endl;
            break;
        }
    }
    //回收资源
    close(fd);
    close(cfd);
#if IS_DEBUG
    cout << "close succeed!!!" << endl;
#endif
    return 0;
}