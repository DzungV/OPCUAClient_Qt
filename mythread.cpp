#include "mythread.h"


MyThread::MyThread(QObject *parent)
    : QThread{parent}
{

}

void MyThread::run()
{
//    int i = 0;
//    while(i == 0)
//    {
//        emit NumberChange(i);

//        this->msleep(100);
//    }
    for(int i = 0; i<10000; i++)

        {

            emit NumberChange(i);

            this->msleep(100);

        }

}
