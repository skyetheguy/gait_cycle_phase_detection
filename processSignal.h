#pragma once
#include <iostream>
#include "sensorData.h"

class processSignal
{

public:

	processSignal();

	float lowPassFilter(int rawData, float beta);

	void updateState();

	bool changedDir();

	int getDir();



private:

	float smoothData;

	float lastReading;

	int direction; // 0 means increasing, 1 means decreasing

	int lastDirection;





};