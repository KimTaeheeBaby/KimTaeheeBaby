#include "mythread.h"

void myThread::initialize()
{
    processObject = new ImgSeqProcessor();
    this->_setUP();
}

void myThread::_setUP()
{
    mode = u8"Video File Model";
    index = 0;
    methodIndex = methodNAME::KNN;
}

void myThread::changeMode(int value)
{
    switch (value)
    {
    case 0:
        mode = u8"Video File Model";
        index = 0;
        break;
    case 1:
        mode = u8"Camera Model";
        index = 1;
        break;
    default:
        cerr << "Unknown Run Mode!!!" << endl;
        break;
    }
}

void myThread::changeMethod(methodNAME myMethod)
{
    if (!(methodIndex == myMethod))
    {
        switch (myMethod)
        {
        case methodNAME::KNN:
            method = "KNN";
            break;
        case methodNAME::MOG:
            method = "MOG";
            break;
        case methodNAME::GMG:
            method = "GMG";
            break;
        case methodNAME::CNT:
            method = "CNT";
            break;
        case methodNAME::GSOC:
            method = "GSOC";
            break;
        case methodNAME::VIBE:
            method = "Vibe";
            break;
        default:
            cerr << "Unknown Method !!!" << endl;
            break;
        }
        methodIndex = myMethod;
    }
}

void myThread::run()
{
    if (index == 0)
        processObject->processVideo(methodIndex);
    else if (index == 1)
        processObject->processCamera(methodIndex);
}
