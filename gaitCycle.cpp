#include "gaitCycle.h"

int gaitCycle::processReadings(sensorData currentData)
{
	float xAccelFilter = xAccelSignal.lowPassFilter(currentData.getXAccel(), 0.2);
	float yAccelFilter = yAccelSignal.lowPassFilter(currentData.getYAccel(), 0.9);
	float zAccelFilter = zAccelSignal.lowPassFilter(currentData.getZAccel(), 0.2);

	float xGyroFilter = xGyroSignal.lowPassFilter(currentData.getXGyro(), 0.2);
	float yGyroFilter = yGyroSignal.lowPassFilter(currentData.getYGyro(), 0.2);
	float zGyroFilter = zGyroSignal.lowPassFilter(currentData.getZGyro(), 0.2);

	cout << yAccelFilter << endl;

	return 0;


}