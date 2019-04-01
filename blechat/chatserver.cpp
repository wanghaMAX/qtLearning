#include "chatserver.h"

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");

chatserver::chatserver(QObject *parent) : QObject(parent){

}

void chatserver::startServer(const QBluetoothAddress &localAdapter){
    rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol,this);
    connect(rfcommServer,SIGNAL(newConnection()),this,SLOT(clientConnect()));
    bool result = rfcommServer->listen(localAdapter);
    if(!result){
        qWarning() << "Cannot bind chat server to" << localAdapter.toString();
    }

    QBluetoothServiceInfo::Sequence classid;
    classid << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));

    serviceinfo.setAttribute(QBluetoothServiceInfo::AdditionalProtocolDescriptorList,classid);
    classid.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));
    serviceinfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classid);
    serviceinfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Bt Chat Server"));
    serviceinfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
                                 tr("Example bluetooth chat server"));
    serviceinfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("qt-project.org"));
    serviceinfo.setServiceUuid(QBluetoothUuid(serviceUuid));
    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    serviceinfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
                                 publicBrowse);
    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    protocol.clear();
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
             << QVariant::fromValue(quint8(rfcommServer->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    serviceinfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                                 protocolDescriptorList);
    serviceinfo.registerService(localAdapter);
}

void chatserver::stopServer(){
    // Unregister service
    serviceinfo.registerService();
    // Close sockets
    qDeleteAll(clientSocket);
    // Close server
    delete rfcommServer;
    rfcommServer = 0;
}

void chatserver::sendMessage(const QString &msg){
    QByteArray text = msg.toUtf8() + '\n';
    foreach(QBluetoothSocket *socket,clientSocket)
        socket->write(text);
}

void chatserver::clientConnect(){
    QBluetoothSocket * socket = rfcommServer->nextPendingConnection();
    if(!socket)
        return;
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSocket()));
    connect(socket,SIGNAL(disconnect()),this,SLOT(clientDisConnect()));
    clientSocket.append(socket);
    emit clientConnect(socket->peerName());
}

void chatserver::clientDisConnect(){
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
    if(!socket)
        return;
    emit clientDisConnect(socket->peerName());
    clientSocket.removeOne(socket);
    socket->deleteLater();
}

void chatserver::readSocket(){
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
    if(!socket)
        return;
    while(socket->canReadLine()){
        QByteArray line = socket->readLine().trimmed();
        emit msgRec(socket->peerName(),QString::fromUtf8(line.constData(),line.length()));
    }
}
