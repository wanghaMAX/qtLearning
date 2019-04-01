#ifndef FUNC_H
#define FUNC_H

#include <QWidget>
#include "add_dialog.h"

namespace Ui {
class func;
}

class func : public QWidget
{
    Q_OBJECT

public:
    explicit func(QWidget *parent = nullptr);
    ~func();

private slots:
    void on_pushButton_clicked();
    void add(QString name,QString id);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::func *ui;
};

#endif // FUNC_H
