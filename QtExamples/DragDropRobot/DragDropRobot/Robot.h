#pragma once

#include <QObject>

class Robot : public QObject
{
    Q_OBJECT

public:
    Robot(QObject *parent);
    ~Robot();
};
