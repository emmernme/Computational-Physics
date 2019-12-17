/*
*	Simulate the Sun, Earth and Jupiter, for different mass factors of Jupiter
*	Compile using:
	g++ simulator_jupiter.cpp -o simulator_jupiter.o  -std=c++11 -O3
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
	int N = 2e5;
	int dim = 3;
	double years = 20.0;

	double mass[] = {1, 10, 950, 1000};

	for (double m : mass){
		Planet Sun("Sun", dim, 1.0,
			-3.631081349384600E-03, 7.477649362162112E-03, 1.840996692980713E-05,
			-8.400385808198203E-06, -1.779086895975768E-06, 2.315365083504170E-07);
		Planet Earth("Earth", dim, 0.000003,
			1.779350187065508E-01, 9.751770110754264E-01, -2.538894112653272E-05,
			-1.719157054168433E-02, 3.104519986569961E-03, -4.949641941010066E-07);
		Planet Jupiter("Jupiter", dim, 0.00095 * m,
			3.738323307080642E-01, -5.213724294602538E+00, 1.325968591237123E-02,
			7.433486238916692E-03, 8.996700648060389E-04, -1.700539642140566E-04);

		// Set up the Solar system
		System Solar_system(10.0, 2);
		Solar_system.add_planet(Sun);
		Solar_system.add_planet(Earth);
		Solar_system.add_planet(Jupiter);

		// Simulate the passing of time
		Solar_system.VelocityVerlet(dim, N, years, "Earth+Jupiter " + to_string(m) + ".dat", to_string(m));
	}

	return 1;
}

