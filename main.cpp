/*
* Author: Keshav Jeewanlall 213508238
*/

/*
* DISCLAMER: The Serial library used in this project is not created by me (Keshav Jeewanlall 2135082238), however,
* some modifications to the library code and the code written to use this library is written by me.
*/

#include<stdlib.h>
#include"SerialPort.h"
#include "FacialRecognition.h"
#include "VideoRecorder.h"




char output[MAX_DATA_LENGTH];
char incomingData[MAX_DATA_LENGTH];

// change the name of the port with the port name of your computer
// must remember that the backslashes are essential so do not remove the

const char* port = "\\\\.\\COM8";
int microOutput1;
int microOutput2;



int main()
{
	FacialRecognition recognise;
	VideoRecorder record;
	SerialPort picMicro(port);

	if (picMicro.isConnected()) 
	{
		cout << "Connection made" << endl << endl;
	}
	else
	{
		cout << "Error in port name" << endl << endl;
	}

	while (picMicro.isConnected()) {

		picMicro.readSerialPort(output, MAX_DATA_LENGTH);
		//microOutput1 = strcmp(output, "a");
		microOutput2 = strcmp(output, "b");

		/*if (microOutput1 == 0)
		{
			recognise.detectFace();
		}*/

		if (microOutput2 == 0)
		{
			record.videoRecord();
		}

	}

	return 0;
}