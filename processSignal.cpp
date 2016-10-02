#include "processSignal.h"


processSignal::processSignal():
direction(0),
lastDirection(0),
lastReading(0)
{}

float processSignal::lowPassFilter(int rawData, float beta) // use Beta as 0.2 for z accel
	{
		lastReading = smoothData;
	    smoothData = smoothData - (beta * (smoothData - rawData));

	    return smoothData;
	}



void processSignal::updateState()
{
	lastDirection = direction;

	if (lastReading < smoothData)
	{
		direction = 0;
	}
	else 
	{
		direction = 1;
	}
}



bool processSignal::changedDir()
{
	if (lastDirection != direction)
	{
		return true;
	}
	return false;
}


int processSignal::getDir()
{
	return direction;
}




