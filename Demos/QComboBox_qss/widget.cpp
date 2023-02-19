#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QListView>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUI()
{
    //设置是否可编辑
    ui->comboBox->setEditable(false);
    //必须有这一句，使用qss对Item的设置才有效
    ui->comboBox->setView(new QListView());
    //去掉下拉框阴影
//    ui->comboBox->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
//    ui->comboBox->view()->window()->setAttribute(Qt::WA_TranslucentBackground);

    QFile file(":/resources/qss/style.qss");
    if(!file.open(QFile::ReadOnly)){
        return;
    }
    QString qss = file.readAll();
    this->setStyleSheet(qss);
}

