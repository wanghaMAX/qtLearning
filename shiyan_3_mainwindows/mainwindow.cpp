#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTcpServer = new QTcpServer(this);
    connect(myTcpServer,SIGNAL(newConnection()),this,SLOT(NewConnect()));
    connect(myTcpSocket,SIGNAL(disconnect()),this,SLOT(deleteLater()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_2_clicked(){
}

void MainWindow::NewConnect(){
}

void MainWindow::deleteLater(){
}
