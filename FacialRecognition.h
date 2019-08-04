/*
* Author: Keshav Jeewanlall 213508238
*/

/*
* DISCLAMER: The Serial library used in this project is not created by me (Keshav Jeewanlall 2135082238), however,
* some modifications to the library code and the code written to use this library is written by me.
*/

#ifndef FACIALRECOGNITIONHEAD_H
#define FACIALRECOGNITIONHEAD_H

#pragma once
#include <opencv\cv.h>

using namespace cv;
using namespace std;

class FacialRecognition
{

private:
	Mat capturedImage;					//Stores the captured image
	vector<Mat> faces;					//Stores the images used for comparisons
	vector<int> ids;					//Stores the IDs of the images

	int im_width;		//Gets width and height of the images used for comparisons
	int im_height;

	Mat original;		//Keeps a copy of the original image
	Mat greyImage;

	vector<Rect_<int>> facePositions;

	Rect face_i;						//Position of the ith face
	Mat getFace;						//Converts to greyscale
	Mat face_resized;										//Resizes the detected face 
	int foundID;			//Gets prediction from face recognizer

public:
	FacialRecognition();
	~FacialRecognition();

	void read_csv(const string & filepath, vector<Mat>& images, vector<int>& labels);
	int detectFace();
};

#endif


