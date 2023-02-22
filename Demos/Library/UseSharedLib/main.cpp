#include "widget.h"

#include <QApplication>

/*
 * 使用QLibrary加载动态库的Demo
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
