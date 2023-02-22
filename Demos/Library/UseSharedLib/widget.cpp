#include "widget.h"
#include "ui_widget.h"
#include <QLibrary>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btn1_clicked()
{
    QLibrary lib("MySharedLib");
    typedef void (*Fun)(void**);
    Fun createInstance = (Fun)lib.resolve("createInstace");
    if(createInstance){
        QWidget* p = nullptr;
        createInstance((void**)&p);
        if(p){
            p->setParent(ui->widget_left);
            p->show();
        }
    }
}

void Widget::on_btn2_clicked()
{
    QLibrary lib("MySharedLib");
    typedef void (*Fun)(void**);
    Fun createInstance = (Fun)lib.resolve("createInstace");
    if(createInstance){
        QWidget* p = nullptr;
        createInstance((void**)&p);
        if(p){
            p->setParent(ui->widget_right);
            p->show();
        }
    }
}
