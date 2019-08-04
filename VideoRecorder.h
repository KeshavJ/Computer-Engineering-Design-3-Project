/*
* Author: Keshav Jeewanlall 213508238
*/

/*
* DISCLAMER: The Serial library used in this project is not created by me (Keshav Jeewanlall 2135082238), however,
* some modifications to the library code and the code written to use this library is written by me.
*/
#ifndef VIDEORECORDERHEAD_H
#define VIDEORECORDERHEAD_H

#pragma once
#include <windows.h>
#include <opencv\cv.h>

using namespace cv;
using namespace std;

class VideoRecorder
{
private:

	int frame_width;
	int frame_height;
	int frames_per_second;
	int fcc;

	Mat frame;

public:
	VideoRecorder();
	~VideoRecorder();

	int videoRecord();
};

#endif



