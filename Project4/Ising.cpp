#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

// Constants
double beta = 1; //  / (k_b * T);
double J = 1; // Energy scale ?

void IsingSetup(){
	int L = 2; // Dimension
	double T = 1.0; // [kT/J]

	// Calculate the partition function, z
	double z = 2*exp(-8 * beta) + 2*exp(8 * beta) + 16;

	// Calculate mean energy, <E>
	double E_mean = 8 * J * ((exp(8*beta) + exp(-8*beta)) / (exp(8*beta) + exp(-8*beta) + 8));

	// Calcularte mean magnetization, |M|
	double M_mean = 8*exp(8 * beta) + 8;

	// Calculate specific heat Cv

	// Calculate suceptibility \chi



}