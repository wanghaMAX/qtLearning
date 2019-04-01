#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QPushButton>
#include <QString>
#include <string.h>
#include <QMessageBox>
#include <QTextBrowser>
#include <QAbstractSocket>

namespace Ui {
class MainWindow;
class TcpServer;
class QPushButton;
class QTcpSocket;
class QString;
class QMessageBox;
class QTextBrowser;
class QAbstractSocket;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpServer* myTCPServer;
    QTcpSocket* myTCPSocket;
    char buffer[1024];
    char* data;
    int flag = 0;
//    QTextBrowser SocketInfo;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPushButton *Button_listen;
    QPushButton *Button_send;
    Ui::MainWindow *ui;

private slots:
    void serverNewConnect();
    void ServerReadData();
    void deleteLater();
    void on_Button_listen_clicked();
    void on_Button_send_clicked();

};

#endif // MAINWINDOW_H
