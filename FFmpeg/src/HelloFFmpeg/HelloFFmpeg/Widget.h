#pragma once

#include <QtWidgets/QWidget>
#include "ui_Widget.h"

extern "C"
{
#include "libavcodec/avcodec.h"
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = Q_NULLPTR);

public slots:
    void on_infoBtn_clicked();
    void on_clearBtn_clicked();

private:
    Ui::WidgetClass ui;
};
