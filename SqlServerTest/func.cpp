#include "func.h"
#include "ui_func.h"
#include <QtDebug>

func::func(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::func)
{
    ui->setupUi(this);
}

func::~func()
{
    delete ui;
}

void func::on_pushButton_clicked(){     //add
    add_dialog *a = new add_dialog;
    connect(a,SIGNAL(back(QString,QString)),this,SLOT(add(QString,QString)));
    a->exec();
}

void func::add(QString name,QString id){
    qDebug() << name+id;
}

void func::on_pushButton_2_clicked(){   //del

}

void func::on_pushButton_3_clicked(){   //find

}

void func::on_pushButton_4_clicked(){   //update

}
