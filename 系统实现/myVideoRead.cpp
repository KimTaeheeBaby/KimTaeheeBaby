#include "myVideoRead.h"

myVideoRead::myVideoRead(string path)
{
    setFile(path);
}

bool myVideoRead::getNextFrame()
{
	if (!video.isOpened())
		return false;
	return video.read(tempImage);
}

void myVideoRead::setFile(string path)
{
    video.open(path);
}
