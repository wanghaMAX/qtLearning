#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class Widget;
class QPushButton;
class QTcpSocket;
class QMessageBox;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    char *data;
    QTcpSocket* myTCPsocket;
    int flag = 0;

private slots:
    void on_pushButton_2_clicked();
    void Read_Data();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
