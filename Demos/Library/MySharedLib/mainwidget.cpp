#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

//开始计算
void MainWidget::on_calBtn_clicked()
{
    bool ok = false;
    int n = ui->input->text().toInt(&ok,10);
    if(ok){
        ui->output->setText(QString::number(calFactorial(n)));
        return;
    }
    ui->output->setText("Error...Please try again");
}

//清空
void MainWidget::on_clearBtn_clicked()
{
    ui->input->clear();
    ui->output->clear();
}

//计算阶乘
long long MainWidget::calFactorial(int n)
{
    if(n < 0){
        return -1;
    }
    if(n == 0){
        return 1;
    }
    return n*calFactorial(n-1);
}
