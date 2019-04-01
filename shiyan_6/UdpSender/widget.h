#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QComboBox>
#include <QFile>
#include <QDateTime>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QTcpSocket *socket;

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    QByteArray socketIP[10];
    QByteArray socketPort[10];
    int socketID = 0;

private slots:
    void readData();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_4_clicked();
};

#endif // WIDGET_H
