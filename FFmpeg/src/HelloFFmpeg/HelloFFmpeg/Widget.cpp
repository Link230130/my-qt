#include "Widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{
    ui.setupUi(this);    
}

void Widget::on_infoBtn_clicked()
{
     QByteArray arr = av_version_info();
     QString str = QString(arr);
     ui.textEdit->setText(str);
}

void Widget::on_clearBtn_clicked()
{
    ui.textEdit->clear();
}
