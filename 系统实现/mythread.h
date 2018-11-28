#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <string>
#include <QString>
#include "ImgSeqProcessor.h"

class myThread: public QThread
{

public:
    myThread()
    {
        this->initialize();
    }
    myThread(std::string str)
    {
        this->initialize();
        setUp(str);
    }
    ImgSeqProcessor *processObject;
    void initialize();
    void setUp(std::string str)
    {
        processObject->setDir(str);
    }
    void _setUP();
    void changeMode(int);
    void changeMethod(methodNAME);
    int getIndex()
    {
        return index;
    }
    int getMethodIndex()
    {
        return methodIndex;
    }
    QString getModeName()
    {
        return mode;
    }
    QString getMethodName()
    {
        return method;
    }
private:
    QString mode;
    QString method;
    int index;
    methodNAME methodIndex;
protected:
    void run();
};



#endif // MYTHREAD_H
