#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTCPsocket = new QTcpSocket();
    connect(myTCPsocket,SIGNAL(readyRead()),this,SLOT(Read_Data()));
}

MainWindow::~MainWindow(){
    connect(ButtonSend,SIGNAL(clicked()),this,SLOT(on_ButtonSend_clicked()));
    connect(ButtonConnect,SIGNAL(clicked()),this,SLOT(on_ButtonConnect_clicked()));
    connect(ButtonUnConnect,SIGNAL(clicked()),this,SLOT(on_ButtonUnConnect_clicked()));
    delete ui;
}

void MainWindow::on_ButtonConnect_clicked(){
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

void MainWindow::Read_Data(){
    qDebug() << "reading!";
    QByteArray buffer;
    buffer = myTCPsocket->readAll();
    if(!buffer.isEmpty()){
        ui->Browser->setText(tr(buffer));
    }
}

void MainWindow::on_ButtonSend_clicked(){
    if(flag == 0){
        qDebug() << "Connection is not connected!";
        QMessageBox::information(this,"Message","Connection is not disabled!");
        return ;
    }
    QString a = ui->lineEdit_3->text();
    QByteArray b = a.toLatin1();
    data = b.data();
    myTCPsocket->write(data,100);
}

void MainWindow::on_ButtonUnConnect_clicked(){
    myTCPsocket->disconnectFromHost();
    flag = 0;
    QMessageBox::information(this,"Message","disconnected!");
}

void MainWindow::on_pushButton_clicked()
{
    if(flag == 0){
        qDebug() << "Connection is not connected!";
        QMessageBox::information(this,"Message","Connection is not disabled!");
        return ;
    }
    QJsonObject obj;
    for(int i=0;i<3;i++){
        int tem = rand()%50;
        int wet = rand()%5;
        int flow = rand()%20;
        int id = ui->lineEdit_3->text().toInt();
        obj.insert("id",id);
        obj.insert("tem",tem);
        obj.insert("wet",wet);
        obj.insert("flow",flow);
    }
    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    myTCPsocket->write(data,data.size());
}
