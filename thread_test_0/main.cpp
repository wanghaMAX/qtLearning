#include <QCoreApplication>
#include "mythread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    mythread *thread1 = new mythread;
    thread1->name = "111";
    thread1->start(QThread::HighestPriority);
    mythread *thread2 = new mythread;
    thread2->name = "222";
    thread2->start(QThread::LowPriority);
    mythread *thread3 = new mythread;
    thread3->name = "333";
    thread3->start(QThread::InheritPriority);
    return a.exec();
}
