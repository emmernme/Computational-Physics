/*
Solving the integral in project 3 using Monte Carlo (MC) random method
*/
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
//#include "matplotlibcpp.h"
//namespace plt = matplotlibcpp;


// Constants
#define _USE_MATH_DEFINES // Pi
double alpha = 2.0;
double exact = 5*M_PI*M_PI / (16*16);
// Approximate ∞ (lambda)
double lim = 0.345; // 0.445
// Number of MC samples
int N = 1e7;
// Tolerance to avoid r1-r2=0 (division by zero)
double tol = 1e-9;

using namespace std;

void MonteCarlo(double lim);
double integration_func(double r1[], double r2[]);

int main(){
	/*MonteCarlo(lim);
	MonteCarlo(1);
	MonteCarlo(2);
	MonteCarlo(3);*/
	MonteCarlo(3);
	return 1;
}
// Calculate length of r-vector
double abs_r(double r[]){
	return sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
}

void MonteCarlo(double lim){
	// Random number generator from C++11
	random_device seeder;
	mt19937 engine(seeder());
	uniform_real_distribution<double> dist(0, lim);

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

	cout << "Lim: " << lim << ", Variance: " << variance << ", integral: " << MC_integral << ", exact: " << exact << endl;
}

// Calculate distance between r-vectors
double dist_r(double r1[], double r2[]){
	return sqrt( pow(r1[0]-r2[0], 2) + pow(r1[1]-r2[1], 2) + pow(r1[2]-r2[2], 2) );
}

// The function to be integrated
double integration_func(double r1[], double r2[]){
	double num = exp (-2 * alpha * (sqrt(pow(r1[0], 2) + pow(r1[1], 2) + pow(r1[2], 2) + sqrt(pow(r2[0], 2) + pow(r2[1], 2) + pow(r2[2], 2)))));

	double dist = abs(sqrt(pow(r1[0]-r2[0], 2) + pow(r1[0])) // dist_r(r1, r2);
	return num / dist;

	if (dist < tol) return 0; 
	return exp(- (abs_r(r1) )); //+ abs_r(r2))); // / dist;
}
