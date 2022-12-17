#pragma once

#include <QObject>

class ColorItem : public QObject
{
    Q_OBJECT

public:
    ColorItem(QObject *parent);
    ~ColorItem();
};
