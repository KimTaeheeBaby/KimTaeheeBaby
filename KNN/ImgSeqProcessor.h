#ifndef IMGSEQPROCESSOR_H
#define IMGSEQPROCESSOR_H

//opencv
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include <opencv2/video/background_segm.hpp>
#include <opencv2/bgsegm.hpp>
#include "Vibe.h"
#include <opencv2/ximgproc/edge_filter.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
//user-define
#include <QObject>
#include <QImage>
#include <QMutex>
#include <QString>
#include <QThread>
#include <QTime>
#include <algorithm>

#define AREATHRESH 400
#define WHRATE 5
#define AREAFILL 0.3

using namespace cv;
using namespace std;
using namespace bgsegm;
using namespace ximgproc;

enum methodNAME {KNN = 0,
                 MOG = 1,
                 GMG = 2,
                 CNT = 3,
                 GSOC = 4,
                 VIBE = 5
                };

class ImgSeqProcessor: public QObject
{
    Q_OBJECT
public:
    ImgSeqProcessor()
    {
        this->initialize();
    }
    ImgSeqProcessor(std::string filePath);
    ~ImgSeqProcessor() {}
    void initialize();
    void setDir(std::string filePath)
    {
        DirPath = filePath;
    }
    void processVideo(methodNAME);
    void processCamera(methodNAME);

    void findObject(const Mat &src, const Mat &mask, Mat &Result, int thresholdBinary, int morphSize);

    bool status()
    {
        return flage;
    }
    void cameraStop()
    {
        cameraFlage = true;
    }
    void videoStop();
    QMutex cameraMutex, videoMutex, videoPauseMutex;
signals:
    void emitImgPtr2(QImage *, QImage *, QImage *, long long);
    void emitFrameCount(long long);
    void emitTime(QString);
public slots:
    void processPause();
    void processContinue();
private:
    bool flage, cameraFlage, videoFlage;
    Mat frame; //current frame
    std::string DirPath;
    long long count;
    Ptr<BackgroundSubtractorKNN> pKNN;
    Ptr<BackgroundSubtractorMOG2> pMOG2;
    Ptr<BackgroundSubtractorGMG> pGMG;
    Ptr<BackgroundSubtractorCNT> pCNT;
    Ptr<BackgroundSubtractorGSOC> pGSOC;
    ViBe_BGS *pVibe = NULL;

    Mat matBgsegm;
    QImage frameResult, imgBgsegm, dectBgsegm;

    const int maxsize = 400;
    void bgsegmInitialize(methodNAME);
    void myApply(Mat &tempFrame, methodNAME myMethod, int framePos);
    void myFilter(uint32_t, uint32_t);
    void cv2QImgRGB(Mat &, QImage &);
    void cv2QImgGRAY(const Mat &, QImage &);
    void frameNumer(Mat &, int number);
};


#endif // IMGSEQPROCESSOR_H
