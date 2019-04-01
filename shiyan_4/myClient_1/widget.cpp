#include "widget.h"
#include "ui_widget.h"

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
    gui_launcher *gl;
    QThread * th1 = new QThread;
    gl->moveToThread(th1);
    QCoreApplication::postEvent(gl,new QEvent(QEvent::User));
}
