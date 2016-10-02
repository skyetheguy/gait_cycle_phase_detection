#pragma once
#include "processSignal.h"
#include <iostream>

using namespace std;


class gaitCycle 
{

public:

	gaitCycle();

	int processReadings(sensorData currentData);

	bool isHeelStrike(float zAccel, int currTime);

	bool isToeOff(float zAccel, int currTime); 

private:

	processSignal xAccelSignal;
	processSignal yAccelSignal;
	processSignal zAccelSignal;

	processSignal xGyroSignal;
	processSignal yGyroSignal;
	processSignal zGyroSignal;

	int lastHeelStrikeTime;
	int lastToeOffTime;
};