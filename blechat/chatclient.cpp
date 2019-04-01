#include "chatclient.h"

chatclient::chatclient()
{

}
void chatclient::startClient(QBluetoothServiceInfo &remoteService){
    if(!socket)
        return;
    // Connect to service
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Create socket";
    socket->connectToService(remoteService);
    qDebug() << "ConnectToService done";
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void chatclient::connected(){
    emit connected(socket->peerName());
}

void chatclient::readSocket(){
    if (!socket)
        return;
    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        emit msgRec(socket->peerName(),QString::fromUtf8(line.constData(), line.length()));
    }
}

void chatclient::sendMsg(const QString &msg){
    QByteArray text = msg.toUtf8() + '\n';
    socket->write(text);
}

void chatclient::stopClient(){
    delete socket;
    socket = 0;
}

