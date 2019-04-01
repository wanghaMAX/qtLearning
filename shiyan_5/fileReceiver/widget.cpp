#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    QDir::setCurrent("/home/wangha/我的坚果云/QT/shiyan_5/build-fileReceiver-Desktop_Qt_5_11_2_GCC_64bit-Debug");
}

Widget::~Widget()
{
    delete ui;
    delete server;
}

void Widget::on_pushButton_clicked()
{
    server->listen(QHostAddress::Any,ui->lineEdit->text().toInt());
    qDebug() << ui->lineEdit->text()+" is listen";
    connect(server,SIGNAL(newConnection()),this,SLOT(NewConnect()));
    connect(server,SIGNAL(disconnect()),this,SLOT(deleteLater()));
//    connect(server,&QTcpServer::disconnect,this,&Widget::deleteLater);
}

void Widget::NewConnect(){
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(readyRead()),this,SLOT(ServerReadData()));
    qDebug() << "new connect";
}

void Widget::deleteLater(){
    qDebug() << "disconnected!";
    socket->disconnectFromHost();
}

/*
 * ##????##????## header
 * #?#????????? content
 */

void Widget::ServerReadData(){
    QByteArray buffer = socket->readAll();
    QByteArray flag("#");
    QByteArray space(" ");
    qDebug() << buffer;
    // handle header
    do{
        if(buffer[0]==flag[0]&&buffer[1]==flag[0]&&fileName == ""&&fileSize == ""){
            curSize = 0;
            int i = 2;
            int j = 0;
            while(buffer[i] != flag[0]){
                fileName[i-2] = buffer[i];
                i++;
            }
            i += 2;
            while(buffer[i] != flag[0]){
                fileSize[j++] = buffer[i++];
            }
            file.setFileName(fileName);
            if(file.exists()){
                file.remove();
                file.setFileName(fileName);
            }
            tempName = fileName;
            qDebug() << fileName;
            qDebug() << fileSize;
            buffer.remove(0,i+2);
            qDebug() << buffer;
        }else if(buffer[0]==flag[0]&&buffer[1]!=flag[0]&&fileName != ""&&fileSize != ""){
            //handle package
            qDebug() << "handle package";
            bufs.clear();
            int i = 1;
            int j = 0;
            while(buffer[i] != flag[0]){
                // get the number
                number[i-1] = buffer[i];
                i++;
            }
            i++;
            qDebug() << number;

            qDebug() << "get the content";
            // get the content to buf
            while(buffer[i] != flag[0]){
                bufs[j++] = buffer[i];
                i++;
            }
            qDebug() << bufs;
            buffer.remove(0,i+1);
            qDebug() << buffer;
            bool ok = file.open(QIODevice::Append);
            if(false==ok){
                qDebug() << "read error";
            }else{
                file.write(bufs);
            }
            file.close();
            curSize += bufs.size();
            qDebug() << "finish";
            //back to init
            if(curSize == fileSize.toInt()){
                qDebug() << "back yo init";
                fileName = "";
                fileSize = "";
                curSize = 0;
            }
        }else {
            qDebug() << "format error";
        }
    }while(!buffer.isEmpty());
    if(tempName.endsWith(".jpg")||tempName.endsWith(".png")||tempName.endsWith(".PNG")){
        QFile tempfile(tempName);
        tempfile.open(QIODevice::ReadOnly);
        QByteArray context = tempfile.readAll();
        tempfile.close();
//        QPixmap img;
//        img.loadFromData(context);
//        img.save(tempName);
        QString contexts;
        contexts.prepend(context);
        QPixmap img = stringTopixmap(contexts);
        img.save(tempName);
    }
}

void Widget::on_pushButton_3_clicked()
{
    //show
        QFile file("/home/wangha/我的坚果云/QT/shiyan_5/12");
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug() << "read error!";
        }else{
            ui->textBrowser->setText(file.readAll());
        }
}

QPixmap Widget::stringTopixmap( const QString& pic){
    QByteArray byte_array = QByteArray::fromBase64(pic.toLocal8Bit());
    QPixmap pix;
    QDataStream data_stream(&byte_array,QIODevice::ReadOnly);
    qDebug() << "where2";
    data_stream >> pix;
    qDebug() << "where2";
    return pix;
}
