#include "widget.h"
#include "ui_widget.h"
#include "func.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    bool a = OpenDatabase();
    qDebug() << a;
}

bool Widget::OpenDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");//数据库驱动类型为SQL Server
    qDebug()<<"ODBC driver?"<<db.isValid();
    QString dsn = "DRIVER={SQL SERVER};SERVER=127.0.0.1;DATABASE=stu_manage";
    db.setDatabaseName(dsn);                            //dataBase Name
    db.setUserName("sa");                               //UserName
    db.setPassword("sa123456");

    if(!db.open())                                      //open
    {
        qDebug()<<db.lastError().text();
        return false;
    }
    else
        qDebug()<<"database open success!";
    return true;
}

void Widget::on_pushButton_2_clicked()
{
    QString Username = ui->lineEdit->text();
    QString PassWd = ui->lineEdit_2->text();
    if(!db.open()){
        qDebug() << "数据库操作失败";
        return;
    }
    QSqlQuery query;
    bool success = query.exec("select userName,PassWd from stu_manage.table_students where userName = "+Username);  //执行查询语句。dbo.test2是该表格
    if(!success){
        qDebug() << "查询user fail";
        return;
    }else{
        qDebug() << "查询user succeed";
        if(PassWd == query.value(1).toString()){
                qDebug() << "load succeed";
                func func;
                func.show();
        }
    }
}


void Widget::on_pushButton_3_clicked(){
    qDebug() << "windows";
    func *funcs = new func();
    funcs->show();
}
