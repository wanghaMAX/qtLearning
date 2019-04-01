#include "add_dialog.h"
#include "ui_add_dialog.h"

add_dialog::add_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_dialog)
{
    ui->setupUi(this);
}

add_dialog::~add_dialog()
{
    delete ui;
}

void add_dialog::on_buttonBox_accepted()
{
    QString name = ui->lineEdit->text();
    QString id = ui->lineEdit_2->text();
    emit back(name,id);
}
