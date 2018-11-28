#ifndef MYVIDEOREAD_H

#include <opencv2\videoio.hpp>
#include <opencv2\core.hpp>
#include <string>
using std::string;
using namespace cv;

class myVideoRead
{
public:
	myVideoRead() {};
	myVideoRead(string);
	~myVideoRead() {};
    void setFile(string);
	bool getNextFrame();
	Mat getFrame() { return tempImage; };
private:
	VideoCapture video;
	Mat tempImage;
};



#endif MYVIDEOREAD_H
