/*
*	Simulate the Sun and Earth and Jupiter, for different beta values of the Universe
*	Compile using:
	g++ simulator_beta.cpp -o simulator_beta.o  -std=c++11 -O3
*/
#include <iostream>
#include <cmath>
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
	int N = 200000;
	int dim = 3;
	double years = 50.0;

	double betas[] = {2.0, 2.5, 2.8, 2.9, 2.95, 2.99, 3};

	for (double beta : betas){
		Planet Sun("Sun", dim, 1.0,
					0.0, 0.0, 0.0, 
					0.0, 0.0, 0.0);
		Planet Earth("Earth", dim, 0.00003,
					1.0, 0.0, 0.0,
					0.0, (2*M_PI + 0.1) / 365, 0); // Velocities in AU/day
					
		System Solar_system(10.0, beta);
		Solar_system.add_planet(Sun);
		Solar_system.add_planet(Earth);

		// Simulate the passing of time
		Solar_system.VelocityVerlet(dim, N, years, "Beta "+ to_string(beta) +".data");
	}
	return 1;
}