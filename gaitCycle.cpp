#include "gaitCycle.h"

gaitCycle::gaitCycle():
lastHeelStrikeTime(0),
lastToeOffTime(0),
lastState(0)
{}

int gaitCycle::processReadings(sensorData currentData)
{
	float xAccelFilter = xAccelSignal.lowPassFilter(currentData.getXAccel(), 0.2);
	float yAccelFilter = yAccelSignal.lowPassFilter(currentData.getYAccel(), 0.9);
	float zAccelFilter = zAccelSignal.lowPassFilter(currentData.getZAccel(), 0.2);

	float xGyroFilter = xGyroSignal.lowPassFilter(currentData.getXGyro(), 0.2);
	float yGyroFilter = yGyroSignal.lowPassFilter(currentData.getYGyro(), 0.2);
	float zGyroFilter = zGyroSignal.lowPassFilter(currentData.getZGyro(), 0.2);

	//cout << currentData.getTime() << "," << xAccelFilter << "," << yAccelFilter << "," << zAccelFilter << "," << xGyroFilter << "," << yGyroFilter << "," << zGyroFilter << endl;

	xAccelSignal.updateState(currentData.getTime(), xAccelFilter);
	yAccelSignal.updateState(currentData.getTime(), yAccelFilter);
	zAccelSignal.updateState(currentData.getTime(), zAccelFilter);

	xGyroSignal.updateState(currentData.getTime(), xGyroFilter);
	yGyroSignal.updateState(currentData.getTime(), yGyroFilter);
	zGyroSignal.updateState(currentData.getTime(), zGyroFilter);


	// USED TO DETECT HEEL STRIKE AND TOE-OFF/TAKE OFF USING SPIKES IN Z-ACCEL
	if (zAccelSignal.changedDir())
	{
		if (zAccelSignal.getDir() == 1) // IF DIRECTION CHANGED TO DECREASING WE HAVE A MAX POINT
		{
			// HANDLE MAX POINT
			cout << "MAX POINT @time " << zAccelSignal.getLastTime() << " value " << zAccelSignal.getLastReading() << endl;

			if (isToeOff(zAccelSignal.getLastReading(), currentData.getTime()))
			{
				cout << "\n=======================\n" << " ** TOE OFF ** " << "\n=======================\n\n" ;
				lastState = 2;
				return 2;
			}
		}
		else // IF DIRECTION CHANGED TO INCREASING WE HAVE A MIN POINT
		{
			// HANDLE MIN POINT
			cout << "MIN POINT @time " << zAccelSignal.getLastTime() << " value " << zAccelSignal.getLastReading() << endl;


			if (isHeelStrike(zAccelSignal.getLastReading(), currentData.getTime()))
			{
				cout << "\n=======================\n" << " ** HEEL STRIKE ** " << "\n=======================\n\n" ;
				lastState = 1;
				return 1;
			}
		}
	}


	if (xGyroSignal.isFlat() && yGyroSignal.isFlat() && zGyroSignal.isFlat() && lastState != 10)
	{
		cout << "\n=======================\n" << " ** NOT MOVING ** " << currentData.getTime() << "\n=======================\n\n" ;
		lastState = 10;
		return 10;
	}


	return 0;


}


bool gaitCycle::isHeelStrike(float zAccel, int currTime)
{
	if (zAccel < 3000 && (currTime - lastHeelStrikeTime) > 150)
	{
		lastHeelStrikeTime = currTime;
		return true;
	}
	return false;
}

bool gaitCycle::isToeOff(float zAccel, int currTime)
{
	if (zAccel > 15500 && (currTime - lastToeOffTime) > 150)
	{
		lastToeOffTime = currTime;
		return true;
	}
	return false;
}