#include "clientui.h"
#include "ui_clientui.h"

clientUI::clientUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientUI)
{
    ui->setupUi(this);
}

clientUI::~clientUI()
{
    delete ui;
}

void clientUI::on_pushButton_3_clicked(){
    if(ui->lineEdit_4->text()!=""&&ui->lineEdit_5->text()!=""){
        QString ip = ui->lineEdit_4->text();
        quint16 port =quint16(ui->lineEdit_5->text().toInt());
        myTcpSocket->connectToHost(ip,port);
            if(!myTcpSocket->waitForConnected(5000)){
                qDebug() << "Connection failed!";
                return;
            }
    }
}

void clientUI::on_pushButton_4_clicked(){
    myTcpSocket->disconnectFromHost();
}


void clientUI::on_pushButton_clicked(){
    QJsonObject obj;
    int tem = ui->lineEdit_3->text().toInt();
    int wet = ui->lineEdit_2->text().toInt();
    int v = ui->lineEdit->text().toInt();
    obj.insert("tem",tem);
    obj.insert("wet",wet);
    obj.insert("v",v);
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    myTcpSocket->write(data,data.size());
}

void clientUI::on_pushButton_2_clicked(){
    QJsonObject obj;
    int tem = rand()%100;
    int wet = rand()%100;
    int v = rand()%100;
    obj.insert("tem",tem);
    obj.insert("wet",wet);
    obj.insert("v",v);
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    myTcpSocket->write(data,data.size());
}
