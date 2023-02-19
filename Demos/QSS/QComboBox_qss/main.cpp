#include "widget.h"

#include <QApplication>

/*
该示例演示了QComboBox的美化示例
比较特别的是，想要美化QComboBox展开后的样式，
首先要设置一下View
    像这样：comboBox->setView(new QListView());
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
