#include "Widget.h"

#include <QApplication>

/**
 * 该示例演示了利用QPainterPath绘制贝塞尔曲线，通过拖动四个点可以实时观察到曲线的绘制情况
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
