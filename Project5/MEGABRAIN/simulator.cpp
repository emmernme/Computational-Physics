/*
*	SIMULATE THE SHIT OUT OF THIS PROJECT
**	Compile using
e
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
	int N = 1000;
	int dim = 3;
	double years = 5.0;

	// Set up the planets
	Planet Sun("Sun", 1, 0, 0, 0, 0, 0, 0);
	Planet Earth("Earth", 0.00003, 1, 0, 0, 0, 6.3, 0);

	// Set up the Solar system
	System Solar_system(10.0);
	Solar_system.add_planet(Sun);
	Solar_system.add_planet(Earth);

	// Simulate the passing of time
	Solar_system.VelocityVerlet(dim, N, years);

	return 1;
}

