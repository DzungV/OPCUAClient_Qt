#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    void run();
    bool bStop;

signals:
    void NumberChange(int);

};

#endif // MYTHREAD_H
