#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QPushButton>
//#include <QAbstractSocket>

namespace Ui {
class MainWindow;
}

extern int s;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer* myTcpServer;
    QTcpSocket* myTcpSocket;

private slots:
    void on_pushButton_2_clicked();
    void NewConnect();
    void deleteLater();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
