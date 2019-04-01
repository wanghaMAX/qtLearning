#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "config.h"

class MyTcpSocket:public QObject
{
    Q_OBJECT
public:
    MyTcpSocket();
    //void connect_to_server();
    void send_command();
    void send_command(int code,QString str);
    void send_file();
    void set_file(QString filePath);

private:
    QTcpSocket *command_socket;
    QTcpSocket *file_socket;
    QTcpServer *tcpServer_c;
    QTcpServer *tcpServer_f;

    QFile file;
    QString filename;
    qint64 filesize;
    qint64 recvSize;
    qint64 sendSize;
public slots:
    void on_read_command();
    void on_read_file();
    void on_connect_c();
    void on_connect_f();
};

#endif // MYTCPSOCKET_H
