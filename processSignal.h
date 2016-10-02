#pragma once
#include <iostream>
#include <deque>
#include <complex>
#include "sensorData.h"
#include "constants.h"

using namespace std;

class processSignal
{

public:

	processSignal();

	float lowPassFilter(int rawData, float beta);

	void updateState(int time, float sensorValue);

	bool changedDir();

	int getDir();

	float getLastReading();

	int getLastTime();

	bool isFlat();




private:

	float smoothData;
	float lastReading;

	int direction; // 0 means increasing, 1 means decreasing
	int lastDirection;

	int currTime;
	int lastTime;

	std::deque<float> dataRecord;





};