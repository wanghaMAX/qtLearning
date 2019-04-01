#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QAbstractSocket>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextBrowser>
#include <QList>


namespace Ui {
class Widget;
class QPaintEvent;
class QPainter;
class QPen;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpServer* myTcpServer;
    QTcpSocket* myTcpSocket;
    QList<QTcpSocket *> myTcpSocketList;

private slots:
    void on_pushButton_listen_clicked();
    void NewConnect();
    void paintEvent(QPaintEvent *paint);
    void ServerReadData();
    void deleteLater();

private:
    QByteArray buffer;
    int ids = 0;
    int num = 0;
    int i = 0;
    int da[10] = {100,100,100,100,100,100,100,100,100,100};
    int da1[10] = {100,100,100,100,100,100,100,100,100,100};
    qintptr id[10];

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
