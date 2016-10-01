#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main( )
{

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


}