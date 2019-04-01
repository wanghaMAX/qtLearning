#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <QDir>
#include <QList>
#include <QPixmap>
#include <QDataStream>

namespace Ui {
class Widget;
class QTcpServer;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpServer *server;
    QTcpSocket *socket;
    QPixmap  stringTopixmap(const QString& pic );

private slots:
    void on_pushButton_clicked();
    void NewConnect();
    void deleteLater();
    void ServerReadData();
    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QByteArray fileName;
    QByteArray fileSize;
    int curSize;
    QByteArray number;
    QFile file;
    QByteArray num;
    QByteArray buf[5000];
    QByteArray bufs;
    QByteArray tempName;

};

#endif // WIDGET_H
