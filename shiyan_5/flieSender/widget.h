#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QTcpSocket>
#include <QTimer>
#include <QMovie>
#include <QString>
#include <QPixmap>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    QString pixmapTostring( const QPixmap& pixmap );

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Widget *ui;
    QString filename;
    qint64 filesize;
    QTcpSocket *socket;
    QTimer timer;
};

#endif // WIDGET_H
