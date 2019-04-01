#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mytcpsocket = new MyTcpSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    //打开文件
    QString filepath = QFileDialog::getOpenFileName(this,"open","../");
    ui->lineEdit->setText(filepath);
    if(!filepath.isEmpty())
        mytcpsocket->set_file(filepath);
}


void MainWindow::on_pushButton_4_clicked()
{
    mytcpsocket->connect_to_server();
}

void MainWindow::on_pushButton_clicked()
{
    //上传
    mytcpsocket->send_command();
}

void MainWindow::on_pushButton_2_clicked()
{
    //下载
}
