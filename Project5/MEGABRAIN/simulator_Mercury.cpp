/*
*	SIMULATE THE SHIT OUT OF THIS PROJECT
*	Compile using
	g++ simulator_Mercury.cpp -o simulator_Mercury.o  -std=c++11 -O3
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <chrono>
#include <time.h>
#include "System.h"
#include "Planet.h"
#include "System.cpp"
#include "Planet.cpp"

using namespace std;

int main (int argv, char **argc){
	int N = 1e8;
	int dim = 2;
	double years = 100.0;

	// Titles end up as the legend for the run in system_plot_multiple.py
	string titles[] = {"No relativity", "Relativity"};
	const bool rel[] = {true, false};

	for(int i = 0; i < sizeof(rel); i++){
		bool r = rel[i];
		string title = titles[i];

		Planet Sun("Sun", dim, 1.0, 0, 0, 0, 0, 0, 0, false);
		// Last argument prevents the sun's position from being stored to file

		Planet Mercury("Mercury", dim, 1.65e-7, 0.3075, 0, 0, 0, 12.44/_YEAR, 0);

		// Set up the Solar system
		System Solar_system(10.0, 2, rel[i]);
		Solar_system.add_planet(Sun);
		Solar_system.add_planet(Mercury);

		// Simulate the passing of time
		Solar_system.VelocityVerletPerihelion(dim, N, years);
	}

	return 1;
}

