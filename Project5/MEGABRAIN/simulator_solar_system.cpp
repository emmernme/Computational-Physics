/*
*	Simulate the entire frickin' solar system
*	Uses NASA values for the initial position and velocity of the various planets
*	Compile using
	g++ simulator_solar_system.cpp -o simulator_solar_system.o  -std=c++11 -O3
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
	int N = 500000;
	int dim = 3; // 3D
	double years = 164.0; // Just enough for Neptune to complete it's orbit

	// Set up the planets with positions and velocities from NASA 
	// Planet PlanetName(Name, dim, mass relative to the Sun, pos_x, pos_y, pos_z, vel_x, vel_y, vel_z);
	Planet Sun("Sun", dim, 1.0,
		-3.631081349384600E-03, 7.477649362162112E-03, 1.840996692980713E-05,
		-8.400385808198203E-06, -1.779086895975768E-06, 2.315365083504170E-07);
	Planet Earth("Earth", dim, 0.000003,
		1.779350187065508E-01, 9.751770110754264E-01, -2.538894112653272E-05,
		-1.719157054168433E-02, 3.104519986569961E-03, -4.949641941010066E-07);
	Planet Jupiter("Jupiter", dim, 0.00095,
		3.738323307080642E-01, -5.213724294602538E+00, 1.325968591237123E-02,
		7.433486238916692E-03, 8.996700648060389E-04, -1.700539642140566E-04);
	Planet Mercury("Mercury", dim, 1.65e-7,
		-3.890645112381974E-01, -1.629803974736235E-01, 2.144738199697205E-02,
		5.558458152239044E-03, -2.451137641094275E-02, -2.513232036732918E-03);
	Planet Venus("Venus", dim, 2.45e-6,
		6.403447196545049E-01, -3.292030038815839E-01, -4.176330947240756E-02,
		9.245033989579347E-03,  1.783848119617762E-02, -2.889642377805590E-04);
	Planet Mars("Mars", dim, 3.3e-7,
		-1.470217455182196E+00, -6.579850747450460E-01, 2.205763511306903E-02,
		6.296493129363556E-03, -1.154811339371407E-02, -3.964135615516856E-04);
	Planet Saturn("Saturn", dim, 2.75e-4, 
		3.696121265219003E+00, -9.322002663437793E+00, 1.495090454345830E-02,
		4.877886323099229E-03,  2.039753372138992E-03, -2.296586453686495E-04);
	Planet Uranus("Uranus", dim, 4.4e-5,
		1.626734576591471E+01,  1.132567092172687E+01, -1.686816903550343E-01,
		-2.276161257391482E-03,  3.044548083490748E-03,  4.084406557400916E-05);
	Planet Neptune("Neptune", dim, 5.15e-5,
		2.922602171634353E+01, -6.421457390572592E+00, -5.413048283120949E-01,
		6.532052949445800E-04,  3.085013872342455E-03, -7.854730908463781E-05);

	// Set up the Solar system - second argument is the universe's beta-value
	System Solar_system(10.0, 2);
	Solar_system.add_planet(Sun);
	Solar_system.add_planet(Earth);
	Solar_system.add_planet(Jupiter);
	Solar_system.add_planet(Mercury);
	Solar_system.add_planet(Venus);
	Solar_system.add_planet(Mars);
	Solar_system.add_planet(Saturn);
	Solar_system.add_planet(Uranus);
	Solar_system.add_planet(Neptune);

	// Simulate the passing of time, and write the resulting data to file
	Solar_system.VelocityVerlet(dim, N, years, "Solar_system.data");
	return 1;
}

