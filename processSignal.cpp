#include "processSignal.h"





float processSignal::lowPassFilter(int rawData, float beta) // use Beta as 0.2 for z accel
	{
	    smoothData = smoothData - (beta * (smoothData - rawData));

	    return smoothData;
	}