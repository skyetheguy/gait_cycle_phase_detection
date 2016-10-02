#pragma once
#include "processSignal.h"
#include <iostream>

using namespace std;


class gaitCycle 
{

public:

	int processReadings(sensorData currentData);

	

private:

	processSignal xAccelSignal;
	processSignal yAccelSignal;
	processSignal zAccelSignal;

	processSignal xGyroSignal;
	processSignal yGyroSignal;
	processSignal zGyroSignal;
};