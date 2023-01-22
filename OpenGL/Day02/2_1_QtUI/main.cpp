#include "mainwindow.h"

#include <QApplication>

/*
Demo演示了在使用EBO（Element Buffer Object）绘制矩形的基础上，
添加与界面的互动操作，包括绘制矩形，清空界面以及切换显示模式三种基本功能。
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
