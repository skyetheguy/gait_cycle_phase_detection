#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "gaitCycle.h"
#include "sensorData.h"
#include "processSignal.h"

#define CSV_LINE_LENGTH 20 


using namespace std;


int main( )
{
	gaitCycle *mainCycle = new gaitCycle;

	int state; // Current state or phase of the gait cycle

	sensorData currentData;


	// OPEN FILE FOR READING
	ifstream infile;
	infile.open("walkData1.csv");

	// USED FOR READING FROM FILE
	string value; 
	vector<string> lineData;


	// WHILE NOT AT EOF KEEP READING LINES WHILE PROCESSING EACH AS WE READ
	while (infile.good())
	{

		for (int i = 0; i <= (CSV_LINE_LENGTH - 2); i++)
		{
			getline(infile, value, ',');
			lineData.push_back(value);

		}

		currentData.setTime( std::stoi(lineData[1], NULL, 10) );
		//cout << std::stoi(lineData[1], NULL, 10) << " ";
		currentData.setXAccel( std::stoi(lineData[2], NULL, 10) );
		//cout << std::stoi(lineData[2], NULL, 10) << " " ;
		currentData.setYAccel( std::stoi(lineData[3], NULL, 10) );
		//cout << std::stoi(lineData[3], NULL, 10) << " " ;
		currentData.setZAccel( std::stoi(lineData[4], NULL, 10) );
		//cout << std::stoi(lineData[4], NULL, 10) << " ";
		currentData.setXGyro( std::stoi(lineData[5], NULL, 10) );
		//cout << std::stoi(lineData[5], NULL, 10) << " " ;
		currentData.setYGyro( std::stoi(lineData[6], NULL, 10) );
		//cout << std::stoi(lineData[6], NULL, 10) << " ";
		currentData.setZGyro( std::stoi(lineData[7], NULL, 10) );
		//cout << std::stoi(lineData[7], NULL, 10) << endl;



		// PROCESS THE DATA JUST TAKEN IN
		state = mainCycle->processReadings(currentData);

		lineData.clear();
	}

	cout <<"finished loop" << endl;


	infile.close(); // CLOSE FILE

   


}










// JUEST A REFERENCE FOR NOW

/*
int RawData;
float SmoothData;
float LPF_Beta = 0.2; // 0<ß<1

  ifstream infile;
  infile.open("z-accel.csv");
  string value;

  ofstream outfile;
  outfile.open("z-accel-filter.csv");

  int count = 0;
  while (infile.good())
  {
  		getline(infile, value);

  		RawData = std::stoi(value, NULL, 10);
   		SmoothData = SmoothData - (LPF_Beta * (SmoothData - RawData));

  		outfile << count << "," << SmoothData << "\n";
  		count++;
  }

  infile.close();
  outfile.close();

  */