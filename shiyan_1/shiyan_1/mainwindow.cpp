#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button1_clicked()
{
    QString str_1=ui->textEdit->toPlainText();
    QString str_2=ui->textEdit_2->toPlainText();
    float num_1=str_1.toFloat();
    float num_2=str_2.toFloat();
    float jia = num_1+num_2;
    float jian = num_1-num_2;
    float cheng = num_1*num_2;
    float chu = num_1/num_2;

    ui->textBrowser->setText("+ : "+QString::number(jia)+"\n"+"- : "+QString::number(jian)+"\n"+"* : "+QString::number(cheng)+"\n"+"/ : "+QString::number(chu));

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << value;
}
