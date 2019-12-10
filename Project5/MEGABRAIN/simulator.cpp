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
using namespace std;

int main (int argv, char *argc){
	int N = 1000;
	int dim = 3;
	int years = 5;

	// Set up the planets
	double Earth_pos[] = {1, 0, 0};
	double Earth_vel[] = {0, 6.3, 0};
	Planet Earth(dim, 0.00003, Earth_pos, Earth_vel);

	double Sun_pos[] = {0, 0, 0};
	double Sun_vel[] = {0, 0, 0};
	Planet Sun(dim, 1, Sun_pos, Sun_vel);

	// Set up the Solar system
	System Solar_system(10);

	// Simulate the passing of time
	Solar_system.VelocityVerlet(dim, N, years, 0);

	return 1;
}

