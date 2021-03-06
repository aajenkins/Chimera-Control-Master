// RC028_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "RC028.h"
#include <windows.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

RC028 pattern1(RC028 DIO)
{
	//generate 100, 200, 300, 400, 500 ns pulses on P1.0 and P2.0
	DIO.setPoint(0, 0, 1, 1, 0, 0, 0, 0, 0, 0b01000000);
	DIO.setPoint(1, 1000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(2, 2000, 1, 1, 0, 0, 0, 0, 0, 0x40);
	DIO.setPoint(3, 4000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(4, 5000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(5, 8000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(6, 9000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(7, 13000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(8, 14000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(9, 19000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(10, 25000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(11, 260000, 1, 0, 0, 0, 0, 0, 0, 0);
	return DIO;
}

RC028 pattern2(RC028 DIO)
{
	unsigned int end = 2047;
	


	////1s test pattern on P1.0 and P2.0
	DIO.setPoint(0, 0, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(1, 1000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(2, 2000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(3, 3000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(4, 4000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(5, 5000, 0, 0, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(6, 6000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(7, 8000, 1, 1, 0, 0, 0, 0, 0, 0);
	DIO.setPoint(8, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	
	return DIO;
}

RC028 patternlong(RC028 DIO)
{
	//full array
	unsigned int end = 2047;
	int time = 0;
	int timeinc = 10;
	int x = 1;
	for (unsigned int i=0;i < end;i++)
	{
		DIO.setPoint(i, time, x, x, 0, 0, 0, 0, 0, 0);
		time += timeinc;
		if (x == 1)
		{
			x = 0;
		}
		else
		{
			x = 1;
		}
	}
	DIO.setPoint(end, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return DIO;
}

int main()
{	
	RC028 DIO;

	DIO = pattern2(DIO);// So I want to construct a DIO object, make setpoint table with it, then write it. 

	DIO.connectasync("FT1VAHJPB"); //This is the serial number of the FTDI chip "FT1VAHJP" - B is added to select channel B

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	DIO.write();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(t2 - t1).count();

	cout << "Write function took " << duration << " microseconds" << endl;

	
	DIO.trigger();
	DIO.disconnect();

	cout << "Finished..." << endl;

    return 0;
}

