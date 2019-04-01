#include "mythread.h"
#include <QtDebug>
myThread::myThread()
{

}

void myThread::run(){
    qDebug() << "123";
    clientUI * cui = new clientUI;
    cui->id = this->id;
    connect(cui,SIGNAL(sig(QString)),this,SLOT(shows(QString)));
    cui->show();
}

void myThread::shows(QString a){
    qDebug() << a;
}
