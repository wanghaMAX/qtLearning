#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QBluetoothAddress>
#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QList>

class chatserver : public QObject
{
    Q_OBJECT
public:
    explicit chatserver(QObject *parent = nullptr);
    ~chatserver();

    void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
    void stopServer();

public slots:
    void sendMessage(const QString &msg);

signals:
    void msgRec(const QString &sender,const QString &msg);
    void clientConnect(const QString &name);
    void clientDisConnect(const QString &name);

private slots:
    void clientConnect();
    void clientDisConnect();
    void readSocket();

private:
    QBluetoothServer *rfcommServer;
    QBluetoothServiceInfo serviceinfo;
    QList<QBluetoothSocket *> clientSocket;

};

#endif // CHATSERVER_H
