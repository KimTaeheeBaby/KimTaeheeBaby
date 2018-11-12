#include "ViBe.h"  

using namespace std;
using namespace cv;

ViBe_BGS::ViBe_BGS(const Mat &_image)
{
	init(_image);
}

/**************** Assign space and init ***************************/
void ViBe_BGS::init(const Mat &_image)
{
	if (!segmentationMap.empty())
		segmentationMap.release();
	segmentationMap = Mat(_image.rows, _image.cols, CV_8UC1);
	if (modelFlage)
		libvibeModel_Sequential_Free(model);
	model = (vibeModel_Sequential_t*)libvibeModel_Sequential_New();
	modelFlage = true;
	if (_image.channels() == 1)
		libvibeModel_Sequential_AllocInit_8u_C1R(model, _image.data, _image.cols, _image.rows);
	else if (_image.channels() == 3)
		libvibeModel_Sequential_AllocInit_8u_C3R(model, _image.data, _image.cols, _image.rows);
	initFlage = true;
}

/**************** update model ********************/
void ViBe_BGS::Update(Mat & _image, Mat & tempMask)
{
	if (_image.channels() == 1)
	{
		libvibeModel_Sequential_Segmentation_8u_C1R(model, _image.data, segmentationMap.data);
		libvibeModel_Sequential_Update_8u_C1R(model, _image.data, segmentationMap.data);
		segmentationMap.copyTo(tempMask);
	}
	else if (_image.channels() == 3)
	{
		libvibeModel_Sequential_Segmentation_8u_C3R(model, _image.data, segmentationMap.data);
		libvibeModel_Sequential_Update_8u_C3R(model, _image.data, segmentationMap.data);
		segmentationMap.copyTo(tempMask);
	}
}