#ifndef TCPFILESERVER_H
#define TCPFILESERVER_H

#include <QDialog>
#include<QtNetwork>
#include<QtWidgets>
class TCPFileserver : public QDialog
{
    Q_OBJECT

public:
    TCPFileserver(QWidget *parent = 0);
    ~TCPFileserver();
public slots:
   void start();
   void acceptConnection();
   void upDateServerProgress();
private:
   QProgressBar *serverProgressBar;
   QLabel *serverStatusLabel;
   QPushButton *startButton;
   QPushButton *quitButton;
   QDialogButtonBox *buttonBox;

   QTcpServer tcpserver;
   QTcpSocket *tcpServerConnection;
   qint64 totalBytes;
   qint64 byteReceived;
   qint64 fileNameSize;
   QString fileName;
   QFile *localFile;
   QByteArray inBlock;
};

#endif // TCPFILESERVER_H
