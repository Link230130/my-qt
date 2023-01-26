#include "mainwindow.h"

#include <QApplication>

/*
Demo演示使用QOpenGLTexture进行纹理贴图
其中纹理是通过uniform进行传入
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
