#include "mainwindow.h"

#include <QApplication>

/*
Demo演示了利用OpenGL绘制三角形，包括顶点着色器和片段着色器的创建、编译及链接
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
