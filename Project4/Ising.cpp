// Compile using:
// g++-9 -std=c++11 Ising.cpp -o Ising.o -larmadillo -O3 -lpthread -fopenmp

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
// Requirements: OpenMP (brew install libomp clang-omp)
#include <omp.h>

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

double IsingSetup(int n, bool random);
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

double IsingSetup(int n, bool random){
	int N = n; // Number of MC cycles

	mat spins = mat(L,L);
	if (random){
		// Set up initial spins randomly
		for (int i = 0; i < L; i++){
			for (int j = 0; j < L; j++){
				int spin = randomSpin();
				spins(i,j) = spin;
			}
		}
	} else {
		// Set all spins to +1
		spins.fill(1);
	}
	//printMat(spins);

	// Set up an array of possible \Delta E-values
	int delta_E[] = {-8, -4, 0, 4, 8};

	double E_trans[] = {exp(-beta * 8), exp(-beta * -8), 1.0, exp(-beta * 4), exp(-beta * -4)};

	double E_sum = 0.0;
	double E_sqrd_sum = 0.0;
	double M_sum = 0.0;
	double M_sqrd_sum = 0.0;
	double M_abs_sum = 0.0;

	// Monte Carlo-loop
	#pragma omp parallel
	for (int i = 0; i < N; i++){
		int x = randomPos(), y = randomPos(); // Random position in the lattice
		double r = dist(engine); // Random probability of flipping

		double E_old = E(spins, x, y);
		double E_new = -E_old; // Flipping the center spin always inverses the energy

		// double P_ratio = exp(-beta * (E_new - E_old));
		double P_ratio;
		if (E_old == -4){
			P_ratio = E_trans[0];
		} else if (E_old == 4){;
			P_ratio = E_trans[1];
		} else if (E_old == 0){
			P_ratio = E_trans[2];
		} else if (E_old == -2){
			P_ratio = E_trans[3];
		} else if (E_old == 2){;
			P_ratio = E_trans[4];
		}

		// Metropolis algo
		if (r <= P_ratio){
			spins(x,y) *= -1;
			E_old = E_new;
		}
	}
	//printMat(spins);

	return E_tot(spins);
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

int main(){
	int n;
	//cout << "How many MC cycles?" << endl;
	//cin >> n;
	for (int n = 100; n < 100000; n += 100){
		cout << IsingSetup(n, true) << " with n=" << n << endl;
	}
	return 0;
}
/* 
Run boy run!
This world is not made for you
Run boy run!
They're trying to catch you
Run boy run!
Running is a victory
Run boy run!
Beauty lies behind the hillsRun boy run!
The sun will be guiding you
Run boy run!
They're dying to stop you
Run boy run!
This race is a prophecy
Run boy run!
Break out from society
Tomorrow is another day
And you won't have to hide away
You'll be a man, boy!
But for now it's time to run
It's time to run!Run boy run!
This ride is a journey to
Run boy run!
The secret inside of you
Run boy run!
This race is a prophecy
Run boy run!
And disappear in the treesTomorrow is another day
And you won't have to hide away
You'll be a man, boy!
But for now it's time to run
It's time to run!
Tomorrow is another day
And when the night fades away
You'll be a man, boy!
But for now it's time to run
It's time to run!
*/
