#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>

class chatclient:public QObject
{
    Q_OBJECT;
public:
    explicit  chatclient();
    ~chatclient();

    void startClient(QBluetoothServiceInfo &remoteService);
    void stopClient();

public slots:
    void sendMsg(const QString &msg);

signals:
    void msgRec(const QString &sender,QString msg);
    void connected(const QString &name);
    void disConnect();

private slots:
    void readSocket();
    void connected();

private:
    QBluetoothSocket * socket;
};

#endif // CHATCLIENT_H
