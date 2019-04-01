#ifndef TCPFILESENDER_H
#define TCPFILESENDER_H

#include <QDialog>
#include<QtNetwork>
#include<QtWidgets>

class TcpFileSender : public QDialog
{
    Q_OBJECT

public:
    TcpFileSender(QWidget *parent = 0);
    ~TcpFileSender();

public slots:
    void start();
    void startTransfer();
    void updateClientProgress(qint64);
    void openFile();

private:
    QProgressBar *clientProgressBar;
    QLabel *clientStatusLabel;
    QPushButton *startButton;
    QPushButton *openButton;
    QPushButton *quitButton;
    QTcpSocket tcpClient;
    QLineEdit *lineEdit1;
    QLabel *label1;
    QLabel *label2;
    QSpinBox *spinbox;

    qint64 totalBytes; //紀錄資料總長度
    qint64 bytesWritten; //紀錄目前已寫出資料的長度
    qint64 bytesToWrite; //紀錄目前尚未寫出資料的長度
    qint64 loadSize; //記錄每筆資料長度

    QString fileName;
    QFile *localFile;
    QByteArray outBlock; //資料輸出儲存緩衝區

};

#endif // TCPFILESENDER_H
