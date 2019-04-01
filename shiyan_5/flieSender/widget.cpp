#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtGlobal>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit_2->setText("127.0.0.1");
}

Widget::~Widget()
{
    delete ui;
    delete socket;
}

void Widget::on_pushButton_clicked()
{
    //find file
    ui->textBrowser->setText("");
    QString filepath = QFileDialog::getOpenFileName(this,"open","../");
    ui->lineEdit->setText(filepath);
    QFileInfo info(filepath);
    filename = info.fileName();
    filesize = info.size();
    ui->textBrowser->append("fileName:"+filename);
    ui->textBrowser->append("fileSize:"+QString::number(filesize));
}

void Widget::on_pushButton_2_clicked()
{
    //show
    if(ui->lineEdit->text() != ""){
        QFile file(ui->lineEdit->text());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "read error!";
        }else{
            ui->textBrowser->setText(file.readAll());
            file.close();
        }
    }else{
        qDebug() << "no file name";
    }
}

void Widget::on_pushButton_3_clicked(){
    //connect
    socket = new QTcpSocket;
    socket->connectToHost(ui->lineEdit_2->text(),ui->lineEdit_3->text().toInt());
    if(!socket->waitForConnected()){
            qDebug() << "Connection failed!";
            return;
        }
    qDebug() << "connected succeed";
}

/*
 * ##????##????## header
 * #?#????????? content
 */

void Widget::on_pushButton_4_clicked(){
    QString dir_name = ui->lineEdit->text();

    QByteArray tempName = filename.toLatin1();
    if(tempName.endsWith(".jpg")||tempName.endsWith(".png")||tempName.endsWith(".PNG")){
        QPixmap img(ui->lineEdit->text());
        QString a = pixmapTostring(img);
        QDir::setCurrent("/tmp");
        QFile p;
        p.setFileName(filename+".img");
        p.open(QIODevice::WriteOnly);
        p.write(a.toLatin1());
        p.close();
        dir_name = "/tmp/"+filename+".img";
    }

    QFile file(dir_name);
    filesize = file.size();

    //header
    QString header = QString("##%1##%2##").arg(filename).arg(filesize);
    socket->write(header.toUtf8());

    //data
    qint64 len = 0;
    int sendsize = 0;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "read error!";
    }
    char buf[4*1024] = {0};
    do{
        len = file.read(buf,sizeof(buf));
        buf[len] = 0;
        qDebug() << len;

        QByteArray bufs("#");
        bufs.append(QString::number(filesize).toLatin1().data());
        bufs.append("#");
        bufs.append(buf);
        bufs.append("#");

        qDebug() << bufs;

        socket->write(bufs,bufs.length());
        sendsize += len;

        qDebug() << sendsize;

        timer.start(50);

    }while (sendsize<filesize);

    if(sendsize==filesize){
        ui->textBrowser->setText("finnish");
    }
}

void Widget::on_pushButton_5_clicked()
{
    // send header
     QString header = QString("##%1##%2").arg(filename).arg(filesize);
     socket->write(header.toUtf8());
     timer.start(20);
}

void Widget::on_pushButton_6_clicked()
{
    // show img
    QMovie *mov = new QMovie(ui->lineEdit->text());
    ui->label_3->setMovie(mov);
    mov->start();
}


QString Widget::pixmapTostring(const QPixmap& pixmap)
{
  QByteArray byte_array;
  QDataStream data_stream(&byte_array,QIODevice::WriteOnly);
  data_stream<<pixmap;
  qDebug() << "bit2";
  qDebug() << byte_array;
  QString res = QString::fromLocal8Bit(byte_array.toBase64());
  return res;
}
