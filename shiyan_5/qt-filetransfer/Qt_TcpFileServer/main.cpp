#include "tcpfileserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPFileserver w;
    w.show();

    return a.exec();
}
