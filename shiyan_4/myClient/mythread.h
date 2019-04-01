#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class mythread:public QThread
{
public:
    mythread();

protected:
    void run();

};

#endif // MYTHREAD_H
