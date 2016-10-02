#include "gaitCycle.h"

gaitCycle::gaitCycle():
lastHeelStrikeTime(0)
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

	xAccelSignal.updateState(currentData);
	yAccelSignal.updateState(currentData);
	zAccelSignal.updateState(currentData);

	xGyroSignal.updateState(currentData);
	yGyroSignal.updateState(currentData);
	zGyroSignal.updateState(currentData);

	if (zAccelSignal.changedDir())
	{
		if (zAccelSignal.getDir() == 1) // IF DIRECTION CHANGED TO DECREASING WE HAVE A MAX POINT
		{
			// HANDLE MAX POINT
			cout << "MAX POINT @time " << zAccelSignal.getLastTime() << " value " << zAccelSignal.getLastReading() << endl;
		}
		else // IF DIRECTION CHANGED TO INCREASING WE HAVE A MIN POINT
		{
			// HANDLE MIN POINT
			cout << "MIN POINT @time " << zAccelSignal.getLastTime() << " value " << zAccelSignal.getLastReading() << endl;

			if (isHeelStrike(zAccelSignal.getLastReading(), currentData.getTime()))
			{
				cout << "\n=======================\n" << " ** HEEL STRIKE ** " << "\n=======================\n\n" ;
				return 0;
			}
		}
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