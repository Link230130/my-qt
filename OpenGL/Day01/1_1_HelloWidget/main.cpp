#include "mainwindow.h"

#include <QApplication>

/*
Demo演示了如何利用QOpenGLWidget进行自定义OpenGL窗口绘制
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
