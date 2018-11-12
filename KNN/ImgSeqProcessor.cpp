#include "ImgSeqProcessor.h"
#include <QDebug>
#include <QMessageBox>

ImgSeqProcessor::ImgSeqProcessor(std::string _DirPath)
{
    this->initialize();
    this->setDir(_DirPath);
}

void ImgSeqProcessor::initialize()
{
    cameraFlage = false;
    flage = false;
    videoFlage = false;

    count = 0;
    DirPath = "";
}

void ImgSeqProcessor::processVideo(methodNAME myMethod)
{
    bgsegmInitialize(myMethod);
    VideoCapture capture(DirPath);
    if (!capture.isOpened())
    {
        cerr << "Unable to open video file: " << DirPath << endl;
        return;
    }
    float frameWidth = (float)capture.get(CAP_PROP_FRAME_WIDTH);
    float frameHeight = (float)capture.get(CAP_PROP_FRAME_HEIGHT);
    float f = min((float)maxsize / frameWidth, (float)maxsize / frameHeight);
    int x = f * frameWidth;
    int y = f * frameHeight;

    Ptr<AdaptiveManifoldFilter> pAMFilter = AdaptiveManifoldFilter::create();

    count = capture.get(CAP_PROP_FRAME_COUNT);
    emit emitFrameCount(count);
    long long now = 0;
    flage = false;
    videoFlage = false;
    videoMutex.lock();
    int64 time = (int64)getTickCount();
    int fps = capture.get(CAP_PROP_FPS);
    double videoDelta = (double)1000 / (double)fps;
    int waitTime = 0;

    int totalMSec = (count * 1000) / fps;
    QString totalMSecTime = QTime::fromMSecsSinceStartOfDay(totalMSec).toString("mm:ss");
    QString totalTime;

    while (1)
    {
        if (!capture.read(frame))
        {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            break;
        }
        if (f < 1)
            resize(frame, frame, Size(x, y));

        QString currentMSecTime = QTime::fromMSecsSinceStartOfDay((int)capture.get(CAP_PROP_POS_MSEC)).toString("mm:ss");
        if (totalTime.compare(currentMSecTime + " / " + totalMSecTime) != 0)
        {
            totalTime = currentMSecTime + " / " + totalMSecTime;
            emit emitTime(totalTime);
//            qDebug() << totalTime;
        }

        pAMFilter->filter(frame, frame);

        this->myApply(frame, myMethod, capture.get(CAP_PROP_POS_FRAMES));

//        emit emitImgPtr2(&frameResult, &imgBgsegm, &dectBgsegm, ++now);
        emit emitImgPtr2(&frameResult, &imgBgsegm, &dectBgsegm, capture.get(CAP_PROP_POS_FRAMES));
        videoPauseMutex.lock();
        videoPauseMutex.unlock();
        if (videoFlage)
            break;
        int64 currentTime = (int64)getTickCount();
        double deltaTime = (double)(currentTime - time) / (double)(getTickFrequency());
        time = currentTime;
        waitTime = videoDelta - 1000 * deltaTime;
        if (waitTime > 0)
            QThread::msleep(waitTime);
    }
    capture.release();
    videoMutex.unlock();
}

void ImgSeqProcessor::processCamera(methodNAME myMethod)
{
    bgsegmInitialize(myMethod);
    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        cerr << "Unable to open camera component: " << endl;
        return;
    }
    cameraFlage = false;
    cameraMutex.lock();

    float frameWidth = (float)capture.get(CAP_PROP_FRAME_WIDTH);
    float frameHeight = (float)capture.get(CAP_PROP_FRAME_HEIGHT);
    float f = min((float)maxsize / frameWidth, (float)maxsize / frameHeight);
    int x = f * frameWidth;
    int y = f * frameHeight;

    while (1)
    {
        if (!capture.read(frame))
        {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            return;
        }
        if (f < 1)
            resize(frame, frame, Size(x, y));

        this->myApply(frame, myMethod, capture.get(CAP_PROP_POS_FRAMES));
        emit emitImgPtr2(&frameResult, &imgBgsegm, &dectBgsegm, -1);
        if (cameraFlage)
            break;
    }
    capture.release();
    cameraMutex.unlock();
}

void ImgSeqProcessor::findObject(const Mat &src, const Mat &mask, Mat &Result, int thresholdBinary, int morphSize)
{
    Mat inBinary;
    threshold(mask, inBinary, thresholdBinary, 255, THRESH_BINARY);
    //medianBlur(result, result, medBlr);
    morphologyEx(inBinary,
                 inBinary,
                 MORPH_OPEN,
                 getStructuringElement(MORPH_ELLIPSE, Size(morphSize, morphSize)));


    src.copyTo(Result);
    Mat labels, stats, centroids;
    int nconcomps = connectedComponentsWithStats(inBinary, labels, stats, centroids);
    Scalar color(0, 0, 255);
    vector<Rect> tempRectangles;
    if (nconcomps > 1)
    {
        int H = mask.rows;
        int W = mask.cols;
        for (int i = 1; i < nconcomps; i++)
        {
            int32_t *p = stats.ptr<int32_t>(i);
            int32_t x = p[0];
            int32_t y = p[1];
            int32_t width = p[2];
            int32_t height = p[3];
            int32_t area = p[4];

            //面积大小限制
            if (area < AREATHRESH)
                continue;
            //矩形框长宽比限制
            float k = (float)width / (float)height;
            auto maxK = WHRATE;
            auto minK = (float)1 / (float)WHRATE;
            if (k >= maxK || k <= minK)
                continue;
            //面积比例限制
            float rate = (float)area / (float)(width * height);
            if (rate < AREAFILL)
                continue;

            if (x == 0 &&
                    y == 0 &&
                    width == W &&
                    height == H)
                continue;
            tempRectangles.push_back(Rect(x, y, width, height));
        }
        //整合矩形框-方法1
        while (1)
        {
            if (tempRectangles.empty())
                return;
            Mat tempMat = Mat::zeros(H, W, CV_8UC3);
            Scalar tempColor(255, 255, 255);
            for (int i = 0; i < tempRectangles.size(); i++)
                rectangle(tempMat, tempRectangles[i], tempColor, FILLED);

            cvtColor(tempMat, tempMat, COLOR_BGR2GRAY);
            threshold(tempMat, tempMat, 127, 255, THRESH_BINARY);

            nconcomps = connectedComponentsWithStats(tempMat, labels, stats, centroids);
            vector<Rect> tempRect;
            for (int i = 1; i < nconcomps; i++)
            {
                int32_t *p = stats.ptr<int32_t>(i);
                tempRect.push_back(Rect(p[0], p[1], p[2], p[3]));
            }
            if (tempRect == tempRectangles)
                break;
            tempRectangles.clear();
            tempRectangles = tempRect;
        }
        for (int i = 0; i < tempRectangles.size(); i++)
            rectangle(Result, tempRectangles[i], color);
    }
}

void ImgSeqProcessor::videoStop()
{
    videoFlage = true;
    if (flage)
        videoPauseMutex.unlock();
}

void ImgSeqProcessor::processPause()
{
    if (!flage)
    {
        videoPauseMutex.lock();
        flage = true;
    }
}

void ImgSeqProcessor::processContinue()
{
    if (flage)
    {
        videoPauseMutex.unlock();
        flage = false;
    }
}

void ImgSeqProcessor::bgsegmInitialize(methodNAME myMethod)
{
    if (myMethod == methodNAME::KNN)
    {
        pKNN = createBackgroundSubtractorKNN();
        pKNN->setDetectShadows(false);
    }
    else if (myMethod == methodNAME::MOG)
    {
        pMOG2 = createBackgroundSubtractorMOG2();
        pMOG2->setDetectShadows(false);
    }
    else if (myMethod == methodNAME::GMG)
        pGMG = createBackgroundSubtractorGMG();
    else if (myMethod == methodNAME::CNT)
        pCNT = createBackgroundSubtractorCNT();
    else if (myMethod == methodNAME::GSOC)
        pGSOC = createBackgroundSubtractorGSOC();
    else if (myMethod == methodNAME::VIBE)
    {
        if (pVibe != NULL)
            delete (pVibe);
        pVibe = new ViBe_BGS();
    }
}

void ImgSeqProcessor::myApply(Mat &tempFrame, methodNAME myMethod, int framePos)
{
    if (myMethod == methodNAME::KNN)
        pKNN->apply(tempFrame, matBgsegm);
    else if (myMethod == methodNAME::MOG)
        pMOG2->apply(tempFrame, matBgsegm);
    else if (myMethod == methodNAME::GMG)
        pGMG->apply(tempFrame, matBgsegm);
    else if (myMethod == methodNAME::CNT)
        pCNT->apply(tempFrame, matBgsegm);
    else if (myMethod == methodNAME::GSOC)
        pGSOC->apply(tempFrame, matBgsegm);
    else if (myMethod == methodNAME::VIBE)
        pVibe->apply(tempFrame, matBgsegm);
    myFilter(5, 7);
    Mat matFrameWithBox;
    findObject(tempFrame, matBgsegm, matFrameWithBox, 127, 5);
    if (framePos >= 0)
        frameNumer(tempFrame, framePos);
    cv2QImgRGB(tempFrame, frameResult);
    cv2QImgRGB(matFrameWithBox, dectBgsegm);
    cv2QImgGRAY(matBgsegm, imgBgsegm);
}

void ImgSeqProcessor::myFilter(uint32_t mediaKernel, uint32_t openKernel)
{
    medianBlur(matBgsegm, matBgsegm, mediaKernel);
    morphologyEx(matBgsegm, matBgsegm, MORPH_OPEN,
                 getStructuringElement(MORPH_ELLIPSE, Size(openKernel, openKernel)));
}

void ImgSeqProcessor::cv2QImgRGB(Mat &tempFrame, QImage &tempFrameResult)
{
    cvtColor(tempFrame, tempFrame, COLOR_BGR2RGB);
    tempFrameResult = QImage((const unsigned char *)(tempFrame.data), tempFrame.cols, tempFrame.rows, QImage::Format_RGB888);
    tempFrameResult.bits();
}

void ImgSeqProcessor::cv2QImgGRAY(const Mat &tempFrame, QImage &tempFrameResult)
{
    tempFrameResult = QImage((const unsigned char *)(tempFrame.data), tempFrame.cols, tempFrame.rows, QImage::Format_Grayscale8);
    tempFrameResult.bits();
}

void ImgSeqProcessor::frameNumer(Mat &tempFrame, int number)
{
    stringstream ss;
    rectangle(tempFrame, cv::Point(10, 2), cv::Point(100, 20),
              cv::Scalar(255, 255, 255), -1); //绘制方块
    ss << number;
    std::string frameNumberString = ss.str();
    putText(tempFrame, frameNumberString.c_str(), cv::Point(15, 15),
            FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0)); //方块中写入帧数
}
