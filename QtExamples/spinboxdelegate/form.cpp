#include "form.h"
#include "ui_form.h"
#include "widgetdelegate.h"
#include <QDebug>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    model = new QStandardItemModel(4,2);
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    WidgetDelegate *delegate = new WidgetDelegate(this);
    ui->tableView->setItemDelegateForColumn(0,delegate);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    connect(delegate,&WidgetDelegate::signalChangeValue,this,&Form::ValueChanged);

    for (int row = 0; row < 4; ++row) {
        QModelIndex index0 = model->index(row, 0, QModelIndex());
        QModelIndex index1 = model->index(row, 1, QModelIndex());

        model->setData(index0, QVariant(-1));
        model->setData(index1,QVariant(12));
    }

}

Form::~Form()
{
    delete ui;
}

void Form::ValueChanged(const QModelIndex &index)
{
    qDebug() << "Form::ValueChanged, index.row=" << index.row() << ",index.column=" << index.column();
    qDebug() << "before data:" << index.data().toInt();
    if(index.data().toInt() > 0){
        model->setData(index,-1)    ;
    }else{
        model->setData(index,1);
    }
    if(index.column() != 0){

    }

    qDebug() << "after data:" << index.data().toInt();
}
