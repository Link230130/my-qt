#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//绘制矩形
void MainWindow::on_drawRect_btn_clicked()
{
    ui->openGLWidget->drawShape(MyOpenGLWidget::Rect);
}

//线条模式
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->openGLWidget->setWireFrame(ui->checkBox->isChecked());
}
//清空界面
void MainWindow::on_clearUI_btn_clicked()
{
    ui->openGLWidget->drawShape(MyOpenGLWidget::None);
}
