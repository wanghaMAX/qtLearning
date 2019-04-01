#include "mythread.h"
#include <QDebug>

mythread::mythread()
{

}

void mythread::run(){
    for(int i=0;i<20;i++)
        qDebug() << this->name;
}

void mythread::cal_1(){

}
