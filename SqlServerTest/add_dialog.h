#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>

namespace Ui {
class add_dialog;
}

class add_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_dialog(QWidget *parent = nullptr);
    ~add_dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::add_dialog *ui;

signals:
    void back(QString name,QString id);
};

#endif // ADD_DIALOG_H
