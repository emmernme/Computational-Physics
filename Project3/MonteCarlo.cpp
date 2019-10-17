/*
Solving the integral in project 3 using Monte Carlo (MC) random method
*/
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

// Constants
#define _USE_MATH_DEFINES // Pi
double alpha = 2;
double exact = 5*M_PI*M_PI / (16*16);
// Approximate ∞ (lambda)
double max_lim = 0.445;
double min_lim = -max_lim;
// Number of MC samples
int N = 1000000;

using namespace std;

void MonteCarlo();
double integration_func(double r1[], double r2[]);

int main(){
	MonteCarlo();
	return 1;
}

void MonteCarlo(){
	// Random number generator from C++11
	random_device seeder;
	mt19937 engine(seeder());
	uniform_real_distribution<double> dist(min_lim, max_lim);

	// Set up integral vars
	double MC_integral = 0;
	double MC_integral_squared = 0;

	// Loop through the desired number of MC samples
	for (int i = 0; i < N; i++){
		// Set up the random position vectors
		double r1[] = {dist(engine), dist(engine), dist(engine)};
		double r2[] = {dist(engine), dist(engine), dist(engine)};

		// Calculate the function value
		double f = integration_func(r1, r2);

		// Add to the integral sum
		MC_integral += f;
		MC_integral_squared += f*f;
	}

	// Calculate the final integral by dividing by the number of MC samples
	MC_integral = MC_integral / ((double) N);
	MC_integral_squared = MC_integral_squared / ((double) N);

	// Calculate variance
	double variance = MC_integral_squared - MC_integral*MC_integral;

	cout << "Variance: " << variance << ", integral: " << MC_integral << ", exact: " << exact << endl;
}

// Calculate length of r-vector
double abs_r(double r[]){
	return sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
}

// The function to be integrated
double integration_func(double r1[], double r2[]){
	return exp(-alpha * (abs_r(r1) + abs_r(r2)));
}
