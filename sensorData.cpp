#include "sensorData.h"



void sensorData::setTime(int value)
{
	time = value;
}


void sensorData::setXAccel(int value)
{
	xAccel = value;
}


void sensorData::setYAccel(int value)
{
	yAccel = value;
}


void sensorData::setZAccel(int value)
{
	zAccel = value;
}


void sensorData::setXGyro(int value)
{
	xGyro = value;
}


void sensorData::setYGyro(int value)
{
	yGyro = value;
}


void sensorData::setZGyro(int value)
{
	zGyro = value;
}

int sensorData::getTime()
{
	return time;
}

int sensorData::getXAccel()
{
	return xAccel;
}

int sensorData::getYAccel()
{
	return yAccel;
}

int sensorData::getZAccel()
{
	return zAccel;
}

int sensorData::getXGyro()
{
	return xGyro;
}

int sensorData::getYGyro()
{
	return yGyro;
}

int sensorData::getZGyro()
{
	return zGyro;
}


