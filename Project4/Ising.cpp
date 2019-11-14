// Compile using:
// c++ Ising.cpp -o Ising.o -larmadillo -O3 -lomp -std=c++11

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
// Requirements: OpenMP (brew install libomp clang-omp)
//#include <omp.h>

using namespace std;
using namespace arma; // Unwraps Armadillo-functions

void printMat(mat a);
int randomSpin(uniform_real_distribution<double> dist, mt19937 engine);
int randomPos(uniform_real_distribution<double> pos, mt19937 engine);
double E_i(mat spins, int x, int y, bool sum, int L);
double E_tot(mat spins, int L);
double M(mat spins, int L);

tuple<double,double,double,double,double,double,double,double,double> MonteCarloIsing(int N, bool random, double T, int L){
	// Constants
	//double T = 1.0; // [kT/J]
	//int L = 2; // Lattice dimension (L x L)
	double beta = 1 / T; //  / (k_b * T);
	// Set up an array of possible \Delta E transition values, delta_E = {-8, -4, 0, 4, 8};
	map<int, double> E_trans = {
	// 	{energy, transition probability}
		{-4, exp(-beta * 8)},
		{-2, exp(-beta * 4)},
		{0, 1.0},
		{2, exp(-beta * -4)},
		{4, exp(-beta * -8)},
	}; // C++11-specific functionality

	// Initialise random
	random_device seeder;
	mt19937 engine(seeder());
	uniform_real_distribution<double> dist(0, 1);
	uniform_real_distribution<double> pos(0, L-1);

	// Set up system
	mat spins = mat(L,L);
	if (random){
		// Set up initial spins randomly
		for (int i = 0; i < L; i++){
			for (int j = 0; j < L; j++){
				int spin = (dist(engine) < 0.5) ? -1 : 1;
				spins(i,j) = spin;
			}
		}
	} else {
		// Set all spins to +1
		spins.fill(1);
	}

	double E_sum = 0.0;
	double E_sqrd_sum = 0.0;
	double M_sum = 0.0;
	double M_sqrd_sum = 0.0;
	double M_abs_sum = 0.0;

	int M_current = M(spins, L);
	double E_current = E_tot(spins, L);

	cout << E_current << endl;

	ofstream output;
	output.open("E_mean-M_mean.dat");

	// Monte Carlo-loop
	for (int i = 0; i < N; i++){
		int x = (int) (pos(engine) + 0.5), y = (int) (pos(engine) + 0.5); // Random position in the lattice

		double r = dist(engine); // Random probability of flipping

		double E_xy = E_i(spins, x, y, false, L);

		// Metropolis algo
		if (r <= E_trans[E_xy]){
			int spin = spins(x,y);
			spins(x,y) = -spin;
			E_xy = -E_xy; // Flipping centre spin inverses the energy
			M_current += -spin;
			E_current += 2*E_xy;
		}
		// Update expectation values
		E_sum += E_current;
		E_sqrd_sum += E_xy*E_xy;
		M_sum += M_current;
		M_sqrd_sum += M_current*M_current;
		M_abs_sum += abs(M_current);

		double norm = 1 / (double)i;
		output << E_sum * norm << "," << M_sum * norm << endl;
	}
	output.close();
	double norm = 1/(double) N; // 1 / #MC cycles
	double E_mean = E_sum * norm;
	double E_sqrd_mean = E_sqrd_sum * norm;
	double M_mean = M_sum * norm;
	double M_sqrd_mean = M_sqrd_sum * norm;
	double M_abs_mean = M_abs_sum * norm;

	double E_variance = (E_sqrd_mean - E_mean*E_mean);
	double M_variance = (M_sqrd_mean - M_abs_mean*M_abs_mean);

	double specific_heat = E_variance / (T*T);
	double suceptibility = M_variance / T;

	return make_tuple(E_mean, E_sqrd_mean, M_mean, M_sqrd_mean, M_abs_sum, E_variance, M_variance, specific_heat, suceptibility);
}

// Calculate the total energy of the system
double E_tot(mat spins, int L){
	double E_count = 0;
	// Loop over all the individual spins' energy contributions
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			E_count -= E_i(spins, i, j, true, L);
		}
	}
	return -E_count;
}

// Calculate the contribution of a single spin and its surroundings to the total energy
double E_i(mat spins, int x, int y, bool sum, int L){
	double E_count = 0;
	/* Only count spins to the left and above, to avoid counting spin interactions twice
	(saves some computing power compared to dividing total energy by two) */
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
	if (!sum){
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
	}

	return -E_count;
}

// Calculate the total magnetization
double M(mat spins, int L){
	double M_count = 0;
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			M_count += spins(i, j);
		}
	}
	return M_count;
}

// Print matrix + the energy
void printMat(mat a, int L){
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			cout << a(i,j) << "	";
		}
		cout << endl;
	}
	cout << "E: " << E_tot(a, L) << endl;
}

// Return -1 or +1 randomly
int randomSpin(uniform_real_distribution<double> dist, mt19937 engine){
	return (dist(engine) < 0.5) ? -1 : 1;
}

// Return a random position in the grid
int randomPos(uniform_real_distribution<double> pos, mt19937 engine){
	return (int) (pos(engine) + 0.5);
}
/*
int main(){
	int n;
	//cout << "How many MC cycles?" << endl;
	//cin >> n;
	for (int n = 1000; n <= 100000; n += 1000){
		cout << MonteCarloIsing(n, true, 1.0, 2) << " with n=" << n << endl;
	}
	return 0;
}
*/
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
