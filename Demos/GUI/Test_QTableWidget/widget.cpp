
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    InitUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitUI()
{
    //初始数据参数设置
    m_headerLabelList << "Header1" << "Header2" << "Header3";
    m_rowCount = 10;

    //需要先设置行、列数，否则设置表头无效
    ui->tableWidget->setColumnCount(m_headerLabelList.size());
    ui->tableWidget->setRowCount(m_rowCount);
    ui->tableWidget->setHorizontalHeaderLabels(m_headerLabelList);

    //设置
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(int r = 0; r < m_rowCount; ++r){
        for(int c = 0; c < m_headerLabelList.size(); ++c){
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(QString("Cell:%1%2").arg(QString::number(r)).arg(QString::number(c)));
            ui->tableWidget->setItem(r,c,item);
        }
    }
}


