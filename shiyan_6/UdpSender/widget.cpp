#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1",8080);
    if(!socket->waitForConnected()){
        qDebug() << "Tcp connect failed!";
        return;
    }
    qDebug() << "8080 is listening with Tcp";
}

Widget::~Widget()
{
    delete ui;
    if(udpSocket){
        delete udpSocket;
    }
    delete socket;
}

void Widget::readData(){
    qDebug() << "read data";
    while(udpSocket->hasPendingDatagrams()){
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        QByteArray data = datagram.data();
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString time = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
        QString sockets = datagram.senderAddress().toString()+":"+QString::number(datagram.senderPort());
        ui->textBrowser->append(time+"-"+ data+"-"+sockets+"#");
        qDebug() << datagram.data();
        if(ui->comboBox->findText(sockets) == -1){
            ui->comboBox->addItem(sockets);
            socketIP[socketID] = datagram.senderAddress().toString().toLatin1();
            socketPort[socketID] = QString::number(datagram.senderPort()).toLatin1();
            qDebug() << socketPort[socketID];
            socketID++;
        }
    }
}

void Widget::on_pushButton_clicked(){
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost,ui->lineEdit->text().toInt());
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    qDebug() << ui->lineEdit->text() + " is bind";
    ui->textBrowser->append(ui->lineEdit->text() + " is bind");
}

void Widget::on_pushButton_2_clicked(){
    delete udpSocket;
    qDebug() << "socket is disbind";
}

void Widget::on_pushButton_3_clicked(){
    QByteArray data = ui->textEdit->toPlainText().toLatin1();
    udpSocket->writeDatagram(data,QHostAddress(ui->lineEdit_2->text()),ui->lineEdit_3->text().toInt());
}

void Widget::on_comboBox_currentIndexChanged(int index){
//    ui->lineEdit_2->setText(socketIP[ui->comboBox->currentIndex()]);
//    ui->lineEdit_3->setText(socketPort[ui->comboBox->currentIndex()]);
    ui->lineEdit_2->setText(socketIP[index]);
    ui->lineEdit_3->setText(socketPort[index]);
}

void Widget::on_pushButton_4_clicked()
{
    QString text = ui->textBrowser->toPlainText();
    ui->textBrowser->clear();
    qDebug() << "send to tcp";
    QFile file("./dat");
    file.open(QIODevice::Append);
    file.write(text.toLatin1());
    file.close();
    socket->write(text.toLatin1());
    socket->waitForBytesWritten();
}
