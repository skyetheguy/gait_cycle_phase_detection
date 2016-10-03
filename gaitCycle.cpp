#include "gaitCycle.h"

gaitCycle::gaitCycle():
lastStateChangeTime(0),
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

	// ***************************
	// CHECK FOR MID SWING
	// ***************************
	if (lastState == TOE_OFF && (currentData.getTime() - lastStateChangeTime) > 20 )
	{
		cout << "\n=======================\n" << " ** MID SWING ** " << currentData.getTime() << "\n=======================\n\n" ;
		lastState = MID_SWING;
		lastStateChangeTime = currentData.getTime();
		return MID_SWING;
	}


	// ***************************
	// CHECK FOR HEEL STRIKE or TOE-OFF/TAKE OFF USING SPIKES IN Z-ACCEL
	// ***************************
	if (zAccelSignal.changedDir())
	{
		if (zAccelSignal.getDir() == DECREASING) // IF DIRECTION CHANGED TO DECREASING WE HAVE A MAX POINT
		{
			// HANDLE MAX POINT
			cout << "MAX POINT @time " << zAccelSignal.getLastTime() << " value " << zAccelSignal.getLastReading() << endl;

			if (isToeOff(zAccelSignal.getLastReading(), currentData.getTime()))
			{
				cout << "\n=======================\n" << " ** TOE OFF ** " << currentData.getTime() << "\n=======================\n\n" ;
				lastState = TOE_OFF;
				lastStateChangeTime = currentData.getTime();
				return TOE_OFF;
			}
		}
		else // IF DIRECTION CHANGED TO INCREASING WE HAVE A MIN POINT
		{
			// HANDLE MIN POINT
			cout << "MIN POINT @time " << zAccelSignal.getLastTime() << " value " << zAccelSignal.getLastReading() << endl;


			if (isHeelStrike(zAccelSignal.getLastReading(), currentData.getTime()))
			{
				cout << "\n=======================\n" << " ** HEEL STRIKE ** " << currentData.getTime() << "\n=======================\n\n" ;
				lastState = HEEL_STRIKE;
				lastStateChangeTime = currentData.getTime();
				return HEEL_STRIKE;
			}
		}
	}

	// ***************************
	// CHECK FOR FOOT FLAT
	// ***************************
	if (yGyroSignal.changedDir() && yGyroSignal.getDir() == INCREASING && yGyroFilter < 4000 && yGyroFilter > -1000 && lastState == HEEL_STRIKE)
	{
		cout << "\n=======================\n" << " ** FOOT FLAT ** " << currentData.getTime() << "\n=======================\n\n" ;
		lastState = FOOT_FLAT;
		lastStateChangeTime = currentData.getTime();
		return FOOT_FLAT;
	}

	// ***************************
	// CHECK FOR HEEL OFF
	// ***************************
	if (yGyroSignal.getDir() == INCREASING && yGyroFilter > 2500 && lastState == FOOT_FLAT)
	{
		cout << "\n=======================\n" << " ** HEEL OFF ** " << currentData.getTime() << "\n=======================\n\n" ;
		lastState = HEEL_OFF;
		lastStateChangeTime = currentData.getTime();
		return HEEL_OFF;
	}



	// ***************************
	// CHECK FOR NOT MOVING
	// ***************************
	if (xGyroSignal.isFlat() && yGyroSignal.isFlat() && zGyroSignal.isFlat() && lastState != NOT_MOVING)
	{
		cout << "\n=======================\n" << " ** NOT MOVING ** " << currentData.getTime() << "\n=======================\n\n" ;
		lastState = NOT_MOVING;
		lastStateChangeTime = currentData.getTime();
		return NOT_MOVING;
	}
	


	
	// NOT WORKING PROPERLY YET
	/*else 
	{
		if (!zGyroSignal.isFlat() && !xGyroSignal.isFlat() && lastState == 10)
		{
			cout << "\n=======================\n" << " ** STARTED MOVING ** " << currentData.getTime() << "\n=======================\n\n" ;
			lastState = 11;
			return 11;
		}
	}*/


	return 0;


}


bool gaitCycle::isHeelStrike(float zAccel, int currTime)
{
	if (zAccel < 3000 && (currTime - lastStateChangeTime) > 150)
	{
		lastStateChangeTime = currTime;
		return true;
	}
	return false;
}

bool gaitCycle::isToeOff(float zAccel, int currTime)
{
	if (zAccel > 15500 && (currTime - lastStateChangeTime) > 150)
	{
		lastStateChangeTime = currTime;
		return true;
	}
	return false;
}