#include "mainwindow.h"

#include <QApplication>

/*
Demo演示了使用QOpenGLShaderProgram进行着色器的编译和链接，
将顶点着色器和片段着色器程序都放在资源文件进行加载，方便管理
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
