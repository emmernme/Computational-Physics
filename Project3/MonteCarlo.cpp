/*
Solving the integral in project 3 using Monte Carlo (MC) random method
Compile using:
g++-9 -std=c++11 MonteCarlo.cpp -o MonteCarlo.o -O3 -lpthread -fopenmp
*/
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
// Requirements: OpenMP (brew install clang-omp)
#include <omp.h>

// Constants
#define _USE_MATH_DEFINES // Pi
double alpha = 2.0;
double exact = 5*M_PI*M_PI / (16*16);
// Number of points
int N = 1e7;
// Tolerance to avoid r1-r2=0 (division by zero)
double tol = 1e-10;

using namespace std;

void MonteCarlo(double lim);
void MonteCarloImproved(double lim);
double integration_func(double r1[], double r2[]);
double int_function_polar(double r1, double r2, double theta_1, double theta_2, double phi_1, double phi_2);
clock_t start, finish;

int main(){
	MonteCarlo(3);
	MonteCarloImproved(3);
	return 1;
}

void MonteCarlo(double lim){
	// Random number generator from C++11
	random_device seeder;
	mt19937 engine(seeder());
	uniform_real_distribution<double> dist(-lim, lim);

	// Prepare Jacobi-determinant
	double jacobi = pow(2 * lim, 6);

	// Set up integral vars
	double integral_sum = 0;
	double sigma_sum = 0;

	// Loop through the desired number of MC samples
	start = omp_get_wtime();
	#pragma omp parallel for reduction(+:integral_sum) reduction(+:sigma_sum)
	for (int i = 0; i < N; i++){
		// Set up the random position vectors
		double r1[] = {dist(engine), dist(engine), dist(engine)};
		double r2[] = {dist(engine), dist(engine), dist(engine)};

		// Calculate the function value for the given points
		double f = integration_func(r1, r2);

		// Add to the integral sum
		integral_sum += f;
		sigma_sum += f*f;
	}
	finish = omp_get_wtime();
	double t1 = (double (finish - start))/CLOCKS_PER_SEC;

	// Calculate the final integral by dividing by the number of MC samples
	double integral = jacobi * integral_sum / ((double) N);
	sigma_sum = sigma_sum / ((double) N);

	// Calculate variance
	double variance = sigma_sum - pow(integral_sum / ((double) N), 2);
	double standard_deviation = jacobi * sqrt(variance / ((double) N));

	cout << "Lim: " << lim << ", N: " << N << ", Time: " << t1 << endl;
	cout << "Variance: " << variance << endl;
	cout << "Integral: " << integral << endl;
	cout << "Exact: " << exact << endl;
	cout << "Standard deviation: " << standard_deviation << endl;
}
void MonteCarloImproved(double lim){
	// Random number generator from C++11
	random_device seeder;
	mt19937 engine(seeder());
	uniform_real_distribution<double> phi_dist(0, 2*M_PI);
	uniform_real_distribution<double> theta_dist(0, M_PI);
	exponential_distribution<double> r_dist(4);

	// Prepare Jacobi-determinant
<<<<<<< HEAD

	double jacobi = 2*2*(2*M_PI)*(2*M_PI)*lim*lim;
=======
	double jacobi = 2*M_PI*2*M_PI * M_PI*M_PI / 16;
>>>>>>> c77511096c649d0e812894e58fd019ae7fadc21d
	// Set up integral vars
	double integral_sum = 0;
	double sigma_sum = 0;
	int i;

	// Loop through the desired number of MC samples
	start = omp_get_wtime();
	#pragma omp parallel for reduction(+:integral_sum) reduction(+:sigma_sum) private(i)
	for (i = 0; i < N; i++){
		// Set up the random polar coordinates
		double coord1[] = {phi_dist(engine), theta_dist(engine), r_dist(engine)};
		double coord2[] = {phi_dist(engine), theta_dist(engine), r_dist(engine)};

		// Calculate the function value for the given points
		double f = int_function_polar(coord1[2], coord2[2], coord1[1], coord2[1], coord1[0], coord2[0]);

		// Add to the integral sum
		integral_sum += f;
		sigma_sum += f*f;
	}
	finish = omp_get_wtime();
	double t2 = (double (finish - start))/CLOCKS_PER_SEC;

	// Calculate the final integral by dividing by the number of MC samples
	double integral = jacobi * integral_sum / ((double) N);
	sigma_sum = sigma_sum / ((double) N);

	// Calculate variance
	double variance = sigma_sum - pow(integral_sum / ((double) N), 2);
	double standard_deviation = jacobi * sqrt(variance / ((double) N));

	cout << endl;
	cout << "Lim: " << lim << ", N: " << N << ", Time: " << t2 << endl;
	cout << "Variance: " << variance << endl;
	cout << "Integral: " << integral << endl;
	cout << "Exact: " << exact << endl;
	cout << "Standard deviation: " << standard_deviation << endl;
}

// Calculate distance between r-vectors
double dist_r(double r1[], double r2[]){
	return sqrt(pow(r1[0]-r2[0], 2) + pow(r1[1]-r2[1], 2) + pow(r1[2]-r2[2], 2));
}

// Calculate length of r-vector
double abs_r(double r[]){
	return sqrt(r[0]*r[0] + r[1]*r[1] + r[2]*r[2]);
}

// The function to be integrated
double integration_func(double r1[], double r2[]){
	double dist = dist_r(r1, r2);
	if (dist < tol) return 0;
	double num = exp(-2*alpha*(abs_r(r1) + abs_r(r2)));

	return num / dist;
}

// Polar integration function
double int_function_polar(double r1, double r2, double theta_1, double theta_2, double phi_1, double phi_2){
	double cosb = cos(theta_1)*cos(theta_2) + sin(theta_1)*sin(theta_2) * cos(phi_1-phi_2);
	double deno = fabs(r1*r1 + r2*r2 - 2*r1*r2*cosb);
	double f = r1*r1*r2*r2*sin(theta_1)*sin(theta_2)/sqrt(deno);

    if (deno > tol){
		return f;
	} else {
		return 0;
	}
}
