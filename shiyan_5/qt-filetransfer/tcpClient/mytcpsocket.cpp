#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket()
{
    command_socket = new QTcpSocket();
    file_socket = new QTcpSocket();
}

void MyTcpSocket::connect_to_server(){
    command_socket->connectToHost(QHostAddress(IP),PORT1);
    file_socket->connectToHost(QHostAddress(IP),PORT2);
    connect(command_socket,SIGNAL(readyRead()),this,SLOT(on_read_command()));
    connect(file_socket,SIGNAL(readyRead()),this,SLOT(on_read_file()));
}

void MyTcpSocket::dis_connect(){
    command_socket->disconnect();
    command_socket->close();
    file_socket->disconnect();
    file_socket->close();
}

void MyTcpSocket::set_file(QString filePath){
    if(filePath.isEmpty()){
        qDebug()<<"设置文件路径失败";
        return;
    }
    QFileInfo info(filePath);
    filename = info.fileName();
    filesize = info.size();
    sendSize = 0;

    if(file.isOpen()){
        file.close();
    }
    file.setFileName(filePath);
    bool isOk = file.open(QIODevice::ReadOnly);
    if(false == isOk)
    {
        qDebug()<<ERROR_CODE_77;
    }
    return;
}

void MyTcpSocket::send_command(){
    QString head = QString("%1##%2##%3").arg(FILE_CODE).arg(filename).arg(filesize);
    qint64 len = command_socket->write(head.toUtf8());
    if(len <= 0){
        qDebug()<<ERROR_CODE_110;
        file.close();
    }
}

void MyTcpSocket::send_download_command(){
    QString str = QString("%1##%2").arg(FILE_DOWN_LOAD).arg(filename);
    qint64 len = command_socket->write(str.toUtf8());
    if(len <= 0){
        qDebug()<<ERROR_CODE_111;
    }
}

void MyTcpSocket::send_file(){
    qint64 len = 0;
    do
    {
        char buf[4*1024] = {0};
        len = file.read(buf,sizeof(buf));

        qDebug()<<file_socket->write(buf,len);

        sendSize += len;
        qDebug()<<len<<sendSize;
    }while(len > 0);

     if(sendSize == filesize)
     {
         qDebug("文件发送完毕");
         file.close();

         file_socket->disconnect();
         file_socket->close();
     }
}

void MyTcpSocket::on_read_command(){
    QByteArray buf = command_socket->readAll();
    qDebug()<<buf;
    int code = QString(buf).section("##",0,0).toInt();
    QString end = QString(buf).section("##",1,1);
    bool isOk;

    switch(code){
    case FILE_CODE:
        filename = QString(buf).section("##",1,1);
        filesize = QString(buf).section("##",2,2).toInt();
        recvSize = 0;

        file.setFileName(filename);
        isOk = file.open(QIODevice::WriteOnly);
        if(false == isOk)
        {
            qDebug()<<"writeonly error 49";
            command_socket->disconnectFromHost();
            command_socket->close();
            return;
        }
        qDebug()<<QString("文件名：%1\n大小:%2 kb").arg(filename).arg(filesize/1024);
        break;
    case FILE_HEAD_REC_CODE:
        if(end == "ok"){
            send_file();
        } else if(end == "error") {
            qDebug()<<"文件头接收失败";
        }
        break;
    case FILE_REC_CODE:
        if(end == "error"){
            qDebug()<<"文件接收失败";
        } else if(end == "ok"){
            qDebug()<<"文件接收成功";
        }
        break;
    case UNZIP_CODE:
        if(end == "error"){
            qDebug()<<"解压失败";
        } else if(end == "ok"){
            qDebug()<<"解压成功";
        }
        break;
    case COMPILE_CODE:
        if(end == "error"){
            qDebug()<<"编译失败";
        } else if(end == "ok"){
            qDebug()<<"编译成功";
            send_download_command();
        }
        break;
    default:
        break;
    }

}

void MyTcpSocket::on_read_file(){
    QByteArray buf = file_socket->readAll();
    qint64 len = file.write(buf);

    qDebug()<<recvSize;
    if(len > 0)
    {
       recvSize += len;
       qDebug()<< len;
    }

    if(recvSize == filesize)
    {
        file.close();
        //QMessageBox::information(this,"完成","文件接收完成");
        file_socket->disconnectFromHost();
        file_socket->close();
    }
}
