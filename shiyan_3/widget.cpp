#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTCPsocket = new QTcpSocket();
    connect(myTCPsocket,SIGNAL(readyRead()),this,SLOT(Read_Data()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked(){
    myTCPsocket->abort(); //disconnect previous link
    QString ip = ui->lineEdit->text();
    quint16 port =quint16(ui->lineEdit_2->text().toInt());
    myTCPsocket->connectToHost(ip,port);
    if(!myTCPsocket->waitForConnected(5000)){
        qDebug() << "Connection failed!";
        QMessageBox::information(this,"Message","Connection failed!");
        flag = 0;
        return;
    }
    flag = 1;
    QMessageBox::information(this,"Message",ip+":"+ui->lineEdit_2->text()+" is connected!");
}

void Widget::on_pushButton_3_clicked()
{
    myTCPsocket->disconnectFromHost();
    flag = 0;
    QMessageBox::information(this,"Message","disconnected!");
}

void Widget::on_pushButton_clicked()
{
//    myTCPsocket->abort(); disconnect previous link
    //    QString ip = ui->lineEdit->text();
    //    quint16 port =quint16(ui->lineEdit_2->text().toInt());
    //    myTCPsocket->connectToHost(ip,port);
    //    if(!myTCPsocket->waitForConnected(5000)){
    //        qDebug() << "Connection failed!";
    //        QMessageBox::information(this,"Message","Connection failed!");
    //        flag = 0;
    //        return;
    //    }
//    flag = 1;

    QJsonObject obj;
    int id = ui->lineEdit_3->text().toInt();
    obj.insert("id",id);
    obj.insert("data",ui->lineEdit_4->text());
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    myTCPsocket->write(data,data.size());
    myTCPsocket->write("\n");
    qDebug() << "send finish";

//    myTCPsocket->disconnectFromHost();
}
void Widget::Read_Data(){
    qDebug() << "reading!";
    QByteArray buffer;
    buffer = myTCPsocket->readAll();
    if(!buffer.isEmpty()){
        ui->textBrowser->setText(tr(buffer));
    }
}
