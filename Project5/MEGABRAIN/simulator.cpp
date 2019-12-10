/*
*	SIMULATE THE SHIT OUT OF THIS PROJECT
*
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <chrono>
#include <time.h>
#include "System.h"
#include "Planet.h"
using namespace std;

int main (int argv, char **argc){
	int N = 1000;
	int dim = 3;
	double years = 5.0;

	// Set up the planets
	Planet Earth(0.00003, 1, 0, 0, 0, 6.3, 0);
	Planet Sun(1, 0, 0, 0, 0, 0, 0);

	// Set up the Solar system
	System Solar_system(10.0);

	// Simulate the passing of time
	Solar_system.VelocityVerlet(dim, N, years);

	return 1;
}

