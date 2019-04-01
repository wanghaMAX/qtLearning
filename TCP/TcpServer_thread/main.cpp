#include <QCoreApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer ser;
    ser.listen(QHostAddress::Any,6666);
    return a.exec();
}
