#pragma once
#include <iostream>
#include "constants.h"


class sensorData
{
public:

	void setTime(int value);
	void setXAccel(int value);
	void setYAccel(int value);
	void setZAccel(int value);
	void setXGyro(int value);
	void setYGyro(int value);
	void setZGyro(int value);

	int getTime();
	int getXAccel();
	int getYAccel();
	int getZAccel();
	int getXGyro();
	int getYGyro();
	int getZGyro();


private: 

	int time;
	int xAccel;
	int yAccel;
	int zAccel;
	int xGyro;
	int yGyro;
	int zGyro;


};