/*
* Author: Keshav Jeewanlall 213508238
*/

/*
* DISCLAMER: The Serial library used in this project is not created by me (Keshav Jeewanlall 2135082238), however,
* some modifications to the library code and the code written to use this library is written by me.
*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\core.hpp>
#include <opencv2\contrib\contrib.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\objdetect.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<stdlib.h>
#include "FacialRecognition.h"


int FacialRecognition::detectFace()
{

	read_csv("C:/Student_Images/csv_file.csv", faces, ids);		//Fills the faces and ids vectors

	im_width = faces[0].cols;		//Gets width and height of the images used for comparisons
	im_height = faces[0].rows;

	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	model->train(faces, ids);			//Creates a face recognizer, trains it with the images used for comparisons

	CascadeClassifier haar_cascade;		//Chooses haar-cascade that is used for face detection
	haar_cascade.load("haarcascade_frontalface_default.xml");
	VideoCapture cap;						//Opens a video feed
	cap.open(0);

	if (!cap.isOpened())
	{
		cout << "ERROR: Could not open camera.";
		return -1;
	}
	while (true)
	{
		cap >> capturedImage;						//Captures an image and stores in the captruedImage

		original = capturedImage.clone();		//Keeps a copy of the original image
		greyImage;
		cvtColor(capturedImage, greyImage, CV_BGR2GRAY);		//Converts the image to greyscale

		haar_cascade.detectMultiScale(greyImage, facePositions);		//Gets the positions of the deteced faces from the image

		for (int i = 0; i < facePositions.size(); i++)
		{
			face_i = facePositions[i];						//Position of the ith face
			getFace = greyImage(face_i);						//Converts to greyscale
			face_resized;										//Resizes the detected face 
			cv::resize(getFace, face_resized, cv::Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
			foundID = model->predict(face_resized);			//Gets predicition from face recognizer


			rectangle(original, face_i, CV_RGB(0, 255, 0), 1);		//Places rectangle over detected face and ID of the recognized faces
			string box_text = format("ID = %d", foundID);
			int pos_x = max(face_i.tl().x - 10, 0);
			int pos_y = max(face_i.tl().y - 10, 0);
			putText(original, box_text, cv::Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);
		}


		imshow("face_recognizer", original);						//Shows original image with recognized faces and their IDs

		//Wait for for 30 milliseconds until any key is pressed.  
		//If the 'Esc' key is pressed (ASCII value of "Esc" is 27), break the while loop.
		//If any other key is pressed, continue the loop 
		//If any key is not pressed within 30 milliseconds, continue the loop 
		if (waitKey(30) == 27)
		{
			return 0;
		}
	}

}


FacialRecognition::FacialRecognition()
{
}

FacialRecognition::~FacialRecognition()
{
}

void FacialRecognition::read_csv(const string& filepath, vector<Mat>& images, vector<int>& labels)
{
	string line, path, classlabel;
	std::ifstream file(filepath.c_str(), ifstream::in);
	if (!file)
	{
		cout << "ERROR: Could not read CSV file.";
	}
	
	while (getline(file, line))					//Loop runs for every line of the CSV file
	{
		stringstream liness(line);
		getline(liness, path, ';');				//Delimiter seperates data
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty())
		{
			images.push_back(imread(path, 0));				//Stores image in vector
			labels.push_back(atoi(classlabel.c_str()));	//Stores ID in vector
		}
	}
}