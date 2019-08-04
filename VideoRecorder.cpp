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
#include "VideoRecorder.h"

VideoRecorder::VideoRecorder()
{
}

VideoRecorder::~VideoRecorder()
{
}

int VideoRecorder::videoRecord()
{
	//Open the default video camera
	VideoCapture cap(0);

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "ERROR: Could not open camera." << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	frame_width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
	frame_height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

	Size frame_size(frame_width, frame_height);
	frames_per_second = 10;
	fcc = CV_FOURCC('M', 'J', 'P', 'G');

	//Create and initialize the VideoWriter object 
	VideoWriter writeVideo("D:/MyVideo.avi", fcc,
		frames_per_second, frame_size, true);

	//If the VideoWriter object is not initialized successfully, exit the program
	if (writeVideo.isOpened() == false)
	{
		cout << "Cannot save the video to a file" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	string window_name = "Security Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"

	while (true)
	{
		frame;
		bool isSuccess = cap.read(frame); // read a new frame from the video camera

		//Breaking the while loop if frames cannot be read from the camera
		if (isSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}

		//write the video frame to the file
		writeVideo.write(frame);

		//show the frame in the created window
		imshow(window_name, frame);

		//Wait for for 30 milliseconds until any key is pressed.  
		//If the 'Esc' key is pressed (ASCII value of "Esc" is 27), break the while loop.
		//If any other key is pressed, continue the loop 
		//If any key is not pressed within 30 milliseconds, continue the loop 
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by the user. Stopping the video" << endl;
			break;
		}
	}

	//Flush and close the video file
	writeVideo.release();

	return 0;
}
