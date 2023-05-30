#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    QStandardItemModel *model;

public slots:
    void ValueChanged(const QModelIndex&);

private:
    Ui::Form *ui;
};

#endif // FORM_H
