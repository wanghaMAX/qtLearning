#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"qpainter.h"

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

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPen pen;
    pen.setWidth(6);
    pen.setColor(Qt::green);
    QPainter painter(this);
    painter.drawLine(314,0,314,250);
    painter.drawLine(0,150,618,150);
    painter.setPen(pen);
    painter.drawPoint(10,10);
    for(int i = 0;i<100;i++){
        double x1 = qrand()%314;
        double x2 = 618-x1;
        double y1 = sin(x1/100);
        double y2 = sin(x2/100);
        painter.drawPoint(int(x1),int(100*y1+150));
        painter.drawPoint(int(x2),int(100*y2+150));
    }
}
