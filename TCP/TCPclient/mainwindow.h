#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>


namespace Ui {
class MainWindow;
class QPushButton;
class QTcpSocket;
class QMessageBox;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    char *data;
    QTcpSocket* myTCPsocket;
    QPushButton* ButtonSend;
    QPushButton* ButtonConnect;
    QPushButton* ButtonUnConnect;
    int flag = 0;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

private slots:
    void on_ButtonConnect_clicked();
    void on_ButtonUnConnect_clicked();
    void Read_Data();
    void on_ButtonSend_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
