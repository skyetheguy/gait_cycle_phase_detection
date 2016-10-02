#include "processSignal.h"


processSignal::processSignal():
direction(0),
lastDirection(0),
lastReading(0),
lastTime(0)
{}

float processSignal::lowPassFilter(int rawData, float beta) // use Beta as 0.2 for z accel
	{
		lastReading = smoothData;
	    smoothData = smoothData - (beta * (smoothData - rawData));

	    return smoothData;
	}



void processSignal::updateState(int time, float sensorValue)
{

	if (dataRecord.size() < 5)
	{
		dataRecord.push_back(sensorValue);
	}
	else
	{
		dataRecord.push_back(sensorValue);
		dataRecord.pop_front();
	}


	lastDirection = direction;
	lastTime = currTime;


	currTime = time;

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

float processSignal::getLastReading()
{
	return lastReading;
}


int processSignal::getLastTime()
{
	return lastTime;
}

bool processSignal::isFlat()
{
	if (dataRecord.size() < 4)
	{
		return false;
	}

	for (int i=0 ; i<= 3 ; i++)
	{
		for (int x= i+1 ; x<=4 ; x++)
		{
			if (abs(dataRecord[i] - dataRecord[x]) > 30)
			{
				return false;
			}
		}
	}
	return true;
}


