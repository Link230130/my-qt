#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include <QLabel>

/*
这是一个使用FFmpeg解码视频并播放的项目，采用软解码纯QPainter绘制
*/

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.show();
    return a.exec();
}
