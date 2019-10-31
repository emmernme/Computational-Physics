#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
using namespace std;
using namespace arma; // Unwraps Armadillo-functions

// Constants
double beta = 1; //  / (k_b * T);
double J = 1; // Energy scale ?
double k_b = 1; // Boltzmann scale ?

int L = 2; // Dimension
double T = 1.0; // [kT/J]

// Initialise random
random_device seeder;
mt19937 engine(seeder());
uniform_real_distribution<double> dist(0, 1);
uniform_real_distribution<double> pos(0, L-1);

void IsingSetup();
void printMat();
int randomSpin();
int randomPos();
double E(mat spins, int x, int y);
double E_tot(mat spins);




double E_tot(mat spins){
	double E_count = 0;
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			E_count -= E(spins, i, j);
		}
	}
	return -E_count;
}
double E(mat spins, int x, int y){
	double E_count = 0;
	if (x != 0){
		E_count += spins(x, y) * spins(x-1, y);
	}
	if (y != 0){
		E_count += spins(x, y) * spins(x, y-1);
	}
	if (x != L-1){
		E_count += spins(x+1, y) * spins(x, y);
	}
	if (y != L-1){
		E_count += spins(x, y) * spins(x, y+1);
	}
	return -E_count;
}

void IsingSetup(){
	int N = 1000; // Number of MC cycles

	// Initialise system
	double E_i = 0;
	double M_i = 0;

	mat spins = mat(L,L);
	// Set up initial spins randomly
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			int spin = randomSpin();
			spins(i,j) = spin;
		}
	}
	printMat(spins);

	// Set up an array of possible \Delta E-values
	int delta_E[] = {-8, -4, 0, 4, 8};

	double E_sum = 0.0;
	double E_sqrd_sum = 0.0;
	double M_sum = 0.0;
	double M_sqrd_sum = 0.0;
	double M_abs_sum = 0.0;

	// Monte Carlo-loop
	for (int i = 0; i < N; i++){
		int x = randomPos();
		int y = randomPos();

		double r = dist(engine); // Random probability of flipping

		// Metropolis algo
		mat new_spins = spins;
		new_spins(x,y) *= -1;
		double E_new = E(new_spins, x, y);
		double E_old = E(spins, x, y);

		double P_ratio = exp(-beta * (E_new - E_old));
		if (r <= P_ratio){
			spins = new_spins;
			E_old = E_new;
		}
	}
	printMat(spins);


/*

	// Calculate the partition function, z
	double z = 2*exp(-8 * beta) + 2*exp(8 * beta) + 16;

	// Calculate mean energy, <E>
	double E_mean = 8 * J * ((exp(8*beta) + exp(-8*beta)) / (exp(8*beta) + exp(-8*beta) + 8));
	// Caclulate mean squared energy, <E^2>
	double E_mean_sqrd = 64*J * (exp(8*beta) + exp(-8*beta)) / (exp(8*beta) + exp(-8*beta) + 8);

	// Calcularte mean magnetization, |M|
	double M_mean = 8*exp(8 * beta) + 8;
	double M_mean_sqrd = 32*exp(8 * beta) + 32;

	// Calculate specific heat, Cv
	double c_v = (E_mean*E_mean - E_mean_sqrd) / (T*T * J*J / (k_b));

	// Calculate susceptibility, χ
	double suceptibility = (M_mean_sqrd - M_mean*M_mean) / (T * J)

*/
}

int main(){
	IsingSetup();
	return 0;
}

// Print matrix + the energy
void printMat(mat a){
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			cout << a(i,j) << "	";
		}
		cout << endl;
	}
	cout << "E: " << E_tot(a) << endl;
}

// Return -1 or +1 randomly
int randomSpin(){
	return (dist(engine) < 0.5) ? -1 : 1;
}

// Return a random position in the grid
int randomPos(){
	return (int) (pos(engine) + 0.5);
}
