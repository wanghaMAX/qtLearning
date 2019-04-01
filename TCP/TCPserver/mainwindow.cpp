#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myTCPServer = new QTcpServer(this);
    connect(myTCPServer,SIGNAL(newConnection()),this,SLOT(serverNewConnect()));
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    connect(Button_listen,SIGNAL(clicked()),this,SLOT(on_Button_listen_clicked()));
    connect(Button_send,SIGNAL(clicked()),this,SLOT(on_Button_send_clicked()));
    delete ui;
}

void MainWindow::serverNewConnect()
{
    myTCPSocket = myTCPServer->nextPendingConnection();
    QMessageBox::information(this,"Message","Get a new Connection!");
    qDebug() << "newConnect!";
    if(myTCPSocket){
        connect(myTCPSocket, SIGNAL(readyRead()), this, SLOT(ServerReadData()));
        connect(myTCPSocket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    }
    ui->SocketInfo->setText("IP"+myTCPSocket->peerAddress().toString());
    QString port_str = QString("port:%1").arg(myTCPSocket->peerPort());
    ui->SocketInfo->append(port_str);
}

void MainWindow::ServerReadData(){
    qDebug() << "have data";
    myTCPSocket->read(buffer,1024);
    QString str(buffer);
    ui->textBrowser_receive->setText(str);
}

void MainWindow::deleteLater(){
    qDebug() << "disconnected!";
    myTCPSocket->disconnectFromHost();
    QMessageBox::information(this,"Message","disable the connection!");
}

void MainWindow::on_Button_listen_clicked(){
    if(!myTCPServer->listen(QHostAddress::Any,quint16(ui->lineEdit_port->text().toInt()))){
        QMessageBox::information(this,"Message","listening error!");
        flag = 0;
    }else{
        QMessageBox::information(this,"Message","Start listening!");
        flag = 1;
    }
}

void MainWindow::on_Button_send_clicked(){
    QString a = ui->lineEdit_send->text();
    QByteArray b = a.toLatin1();
    data = b.data();
    if(flag==0){
        QMessageBox::information(this,"Message","Please listening first!");
        return ;
    }
    if(!data){
        QMessageBox::information(this,"Message","The message is empty!");
    }else{
        int sendRe = myTCPSocket->write(data);
        if(sendRe==-1){
            QMessageBox::information(this,"Message","Sending error!");
        }
    }
}
