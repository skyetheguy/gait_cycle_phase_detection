#pragma once
#include <iostream>
#include "sensorData.h"

class processSignal
{

public:


	float lowPassFilter(int rawData, float beta);



private:

	float smoothData;





};