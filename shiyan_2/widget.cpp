#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTcpServer = new QTcpServer(this);
    connect(myTcpServer,SIGNAL(newConnection()),this,SLOT(NewConnect()));
    connect(myTcpSocket,SIGNAL(disconnect()),this,SLOT(deleteLater()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_listen_clicked(){
    if(!myTcpServer->listen(QHostAddress::Any,quint16(ui->lineEdit_port->text().toInt()))){
            QMessageBox::information(this,"Message","listening error!");
        }
    qDebug() << ui->lineEdit_port->text()+" is listening";
}

void Widget::NewConnect(){
    myTcpSocket = myTcpServer->nextPendingConnection();
    connect(myTcpSocket,SIGNAL(readyRead()),this,SLOT(ServerReadData()));
//    for(int ii=0;ii<10;ii++){
//        if(myTcpSocket->socketDescriptor()==id[ii]){
//            ids = ii;
//            connect(myTcpSocketList[ii],SIGNAL(readyRead()), this, SLOT(ServerReadData()));
//            return ;
//        }
//    }
//    myTcpSocketList.append(myTcpSocket);
//    num++;
//    ids = num - 1;
//    id[num-1] = myTcpSocket->socketDescriptor();
//    qDebug() << "newConnect!";
//    connect(myTcpSocketList[num-1],SIGNAL(readyRead()), this, SLOT(ServerReadData()));
}

void Widget::ServerReadData(){
//    QByteArray buffer = myTcpSocketList[ids]->readAll();
    QByteArray buffer = myTcpSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(buffer);
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        ids++;
        qDebug() << 1;
        if(obj.value("id").toVariant().toInt()==1){
            qDebug() << "have data from 1";
            da[i++] = obj.value("data").toVariant().toInt()+100;
            if(i == 10){
                for(int s=0;s<9;s++){
                    da[s] = da[s+1];
                }
                da[9] = 100;
                i = i - 1;
            }
        }else if (obj.value("id").toVariant().toInt()==2) {
            qDebug() << "have data from 1";
            da1[i++] = obj.value("data").toVariant().toInt()+100;
            if(i == 10){
                for(int s=0;s<9;s++){
                    da1[s] = da1[s+1];
                }
                da1[9] = 100;
                i = i - 1;
            }
        }else{
            qDebug() << "hahha";
        }
        ui->textBrowser->append("data:"+obj.value("data").toString()+" from "+QString::number(obj.value("id").toVariant().toInt()));
        QWidget::update();
    }else {
        qDebug() << 0;
    }
}

void Widget::deleteLater(){
    qDebug() << "disconnected!";
    myTcpSocket->disconnectFromHost();
//    QMessageBox::information(this,"Message","disable the connection!");
}


void Widget::paintEvent(QPaintEvent *paint){
    QPen pen;
    pen.setWidth(6);
    pen.setColor(Qt::red);
    QPainter painter(this);
    painter.setPen(pen);
    int x = 0;
    int y = da[0];
    for(int ii=0;ii<10;ii++){
        if(da[ii]!=100){
            painter.drawLine(x,y,x+50,da[ii]);
            x = x + 50;
            y = da[ii];
        }
    }
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    int x1 = 0;
    int y1 = da1[0];
    for(int ii=0;ii<10;ii++){
        if(da1[ii]!=100){
            painter.drawLine(x1,y1,x1+50,da1[ii]);
            x1 = x1 + 50;
            y1 = da1[ii];
        }
    }
}
