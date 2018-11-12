#pragma once
#include <iostream>
#include <opencv2\opencv.hpp>
#include "vibe-background-sequential.h"

using namespace cv;
using namespace std;

class ViBe_BGS
{
public:
    ViBe_BGS(void) {}
    ViBe_BGS(const Mat &_image);
    ~ViBe_BGS(void)
    {
        deleteSamples();
    }
    void apply(Mat &_image, Mat &tempMask)
    {
        if (_image.empty())
            return;
        if (!initFlage)
        {
            init(_image);
            tempMask = Mat::zeros(_image.rows, _image.cols, CV_8UC1);
            return;
        }
        Update(_image, tempMask);
    }

    uint32_t getNumberOfSamples()
    {
        return libvibeModel_Sequential_GetNumberOfSamples(model);
    }
    uint32_t getMatchingNumber()
    {
        return libvibeModel_Sequential_GetMatchingNumber(model);
    }
    uint32_t getMatchingThreshold()
    {
        return libvibeModel_Sequential_GetMatchingThreshold(model);
    }
    uint32_t getUpdateFactor()
    {
        return libvibeModel_Sequential_GetUpdateFactor(model);
    }

    int32_t setNumberOfSamples(uint32_t value)
    {
        return libvibeModel_Sequential_SetNumberOfSamples(model, value);
    }
    int32_t setMatchingNumber(uint32_t value)
    {
        return libvibeModel_Sequential_SetMatchingNumber(model, value);
    }
    int32_t setMatchingThreshold(uint32_t value)
    {
        return libvibeModel_Sequential_SetMatchingThreshold(model, value);
    }
    int32_t setUpdateFactor(uint32_t value)
    {
        return libvibeModel_Sequential_SetUpdateFactor(model, value);
    }

    void printParameters()
    {
        libvibeModel_Sequential_PrintParameters(model);
    }

    void deleteSamples()
    {
        libvibeModel_Sequential_Free(model);
        segmentationMap.release();
    }
    bool isInit()
    {
        return initFlage;
    }
private:
    void init(const Mat &_image);
    void Update(Mat &_image, Mat &tempMask);

    bool initFlage = false;
    bool modelFlage = false;
    vibeModel_Sequential_t *model = NULL;
    Mat segmentationMap;
};
