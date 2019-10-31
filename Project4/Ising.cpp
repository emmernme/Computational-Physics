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

int L = 5; // Dimension
double T = 1.0; // [kT/J]

// Initialise random
random_device seeder;
mt19937 engine(seeder());
uniform_real_distribution<double> dist(0, 1);
uniform_real_distribution<double> pos(0, L-1);

void IsingSetup();
void printMat(mat a);
int randomSpin();
int randomPos();
double E(mat spins, int x, int y);
double E_tot(mat spins);

// Calculate the total energy of the system
double E_tot(mat spins){
	double E_count = 0;
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			E_count -= E(spins, i, j);
		}
	}
	return -E_count;
}

// Calculate the contribution of a single spin and its surroundings to the total energy
double E(mat spins, int x, int y){
	double E_count = 0;
	if (x != 0){ // If not on leftmost edge, add energy contribution from spin on the left
		E_count += spins(x, y) * spins(x-1, y);
	} else {
		E_count += spins(x, y) * spins(L-1, y);
	}
	if (y != 0){ // If not on top edge, add energy contribution from spin above
		E_count += spins(x, y) * spins(x, y-1);
	} else {
		E_count += spins(x, y) * spins(x, L-1);
	}
	if (x != L-1){ // If not on rightmost edge, add energy contribution from spin on the right
		E_count += spins(x+1, y) * spins(x, y);
	} else {
		E_count += spins(0, y) * spins(x, y);
	}
	if (y != L-1){ // If not on bottom edge, add energy contribution from spin below
		E_count += spins(x, y) * spins(x, y+1);
	} else {
		E_count += spins(x, y) * spins(x, 0);
	}
	return -E_count;
}

void IsingSetup(){
	int N = 50; // Number of MC cycles

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
		cout << "E_new: " << E_new << ", E_old: " << E_old << endl;

		double P_ratio = exp(-beta * (E_new - E_old));
		if (r <= P_ratio){
			spins = new_spins;
			E_old = E_new;
		}
	}
	printMat(spins);
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


// Run, boy, run!
int main(){
	IsingSetup();
	return 0;
}