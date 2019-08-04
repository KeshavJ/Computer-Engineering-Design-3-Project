/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/

/*
* DISCLAMER: This Serial library is not created by me (Keshav Jeewanlall 2135082238), however,
* some modifications to this library code and the code written to use this library is written by me.
* This is an open-source library and code.
* The unmodified library and code can be found on at https://github.com/manashmndl/SerialPort
*/


#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class SerialPort
{
private:
	HANDLE handler;
	bool connected;
	COMSTAT status;
	DWORD errors;
public:
	SerialPort(const char *portName);
	~SerialPort();

	int readSerialPort(char *buffer, unsigned int buf_size);
	bool writeSerialPort(char *buffer, unsigned int buf_size);
	bool isConnected();
};

#endif // SERIALPORT_H