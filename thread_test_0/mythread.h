#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class mythread: public QThread
{
public:
    mythread();
    void run();
    QString name;
private:
    void cal_1();
};

#endif // MYTHREAD_H
