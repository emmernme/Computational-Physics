/*
*	Simulate a Solar System
*	Compile using
	g++ simulator.cpp -o simulator.o  -std=c++11 -O3
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
	int N = 1e7;
	int dim = 3;
	double years = 500.0;

	double velocity[2] = {2.82, 2.83};

	for (double v : velocity){
		Planet Sun("Sun", dim, 1.0,
					0.0, 0.0, 0.0, 
					0.0, 0.0, 0.0);
		Planet Earth("Earth", dim, 0.00003,
					1.0, 0.0, 0.0,
					0.0, (v*M_PI) / 365, 0); // Velocities in AU/day
		System Solar_system(10.0, 2);
		Solar_system.add_planet(Sun);
		Solar_system.add_planet(Earth);
		//Solar_system.add_planet(Jupiter);

		// Simulate the passing of time
		Solar_system.VelocityVerlet(dim, N, years, "Vel "+ to_string(v) +".data", "Velocity"+to_string(v));

	}

	/*Planet Sun("Sun", dim, 1.0, -3.631081349384600E-03, 7.477649362162112E-03, 1.840996692980713E-05, -8.400385808198203E-06, -1.779086895975768E-06, 2.315365083504170E-07);
	Planet Earth("Earth", dim, 0.000003, 1.779350187065508E-01, 9.751770110754264E-01, -2.538894112653272E-05, -1.719157054168433E-02, 3.104519986569961E-03, -4.949641941010066E-07);
	Planet Jupiter("Jupiter", dim, 0.00095, 3.738323307080642E-01, -5.213724294602538E+00, 1.325968591237123E-02, 7.433486238916692E-03, 8.996700648060389E-04, -1.700539642140566E-04); */

	// Set up the Solar system

	// Plot
	//system("python3 ./system_plot.py \"beta=2.data\"");
	return 1;
}

