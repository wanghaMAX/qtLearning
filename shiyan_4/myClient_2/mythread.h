#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QTcpSocket>
#include "clientui.h"

class myThread:public QThread
{
    Q_OBJECT
public:
    myThread();
    int8_t id;
//    QTcpSocket *socket;
public slots:
    void shows(QString);

protected:
    void run();
};

#endif // MYTHREAD_H
