#include "clientui.h"
#include "ui_clientui.h"
#include <QtDebug>
#include <QJsonObject>
#include <QJsonDocument>

clientUI::clientUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientUI)
{
    ui->setupUi(this);
    qDebug() << "666";
    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1",8080);
    qDebug() << "666";
    if(!socket->waitForConnected()){
        qDebug() << "Connection failed!";
        return;
    }
    send();
//    socket->flush();
}

void clientUI::send(){
    while(1){
        QJsonObject obj;
        int tem = qrand()%100;
        int wet = qrand()%100;
        int v = qrand()%100;
        obj.insert("tem",tem);
        obj.insert("wet",wet);
        obj.insert("v",v);
        QJsonDocument doc;
        doc.setObject(obj);
        QByteArray data = doc.toJson(QJsonDocument::Compact);
        socket->write(data,data.size());
        socket->waitForBytesWritten();
        QThread::sleep(2);
    }
}

clientUI::~clientUI()
{
    delete ui;
}

void clientUI::on_pushButton_clicked(){
    qDebug() << "button!";
}
