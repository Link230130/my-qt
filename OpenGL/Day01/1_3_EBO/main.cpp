#include "mainwindow.h"

#include <QApplication>

/*
Demo演示了使用EBO（Element Buffer Object）绘制矩形
特别注意：VAO会记录EBO的绑定及解除，因此如果需要解除EBO的绑定，那么需要在VAO解除绑定前执行；
        而VAO不会记录VBO的绑定及解除，也就是说VBO的解除绑定没有EBO那一条限制
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
