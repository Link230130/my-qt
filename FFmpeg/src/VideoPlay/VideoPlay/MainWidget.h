
#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWidget.h"

#include "ReadThread.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);
    ~MainWidget();

private slots :
    void on_startBtn_clicked();
    void on_selectBtn_clicked();
    void on_pauseBtn_clicked();
    void on_playState(ReadThread::PlayState state);

private:
    ReadThread      *m_readThread;

private:
    Ui::MainWidgetClass ui;
};
