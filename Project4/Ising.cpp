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

// Function declarations
void printMat(mat a);
double E_i(mat spins, int x, int y, bool sum, int L);
double E_tot(mat spins, int L);
double M(mat spins, int L);

vector<double> MonteCarloIsing(int N, bool random, double T, int L, vector<int> &E_count, vector<int> &flip_N){
	// Constants
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
	int flip_count; // Number of accepted flips

	cout << E_current << endl;

	ofstream output;
	output.open("E_mean-M_mean.dat");


	// Monte Carlo-loop
	for (int i = 1; i <= N; i++){
		int x = (int) (pos(engine) + 0.5); // Random position in the lattice
		int y = (int) (pos(engine) + 0.5); // Random position in the lattice

		double r = dist(engine); // Random probability of flipping

		// Calculate the surrounding energy contributions
		double E_xy = E_i(spins, x, y, false, L);

		// Metropolis algo
		if (r <= E_trans[E_xy]){
			flip_count++;
			int spin = spins(x,y);
			spins(x,y) = -spin;
			E_xy = -E_xy; // Flipping centre spin inverses the energy
			M_current += -spin;
			E_current += 2*E_xy;
		}
		flip_N.push_back(flip_count);

		// Update expectation values
		E_sum += E_current;
		E_sqrd_sum += E_xy*E_xy;
		M_sum += M_current;
		M_sqrd_sum += M_current*M_current;
		M_abs_sum += abs(M_current);

		// Count energies to make probability
		if (i > 0.1 * N){
			E_count.push_back(E_current);
		}

		// Calculate the running mean values (for task c)
		double norm = 1 / (double)i;
		output << E_sum * norm << "," << M_sum * norm << endl;
	}

	output.close();

	// Calculate the mean values
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

	vector<double>results;
	results.insert(results.end(), {E_mean, E_sqrd_mean, M_mean, M_sqrd_mean, M_abs_sum, E_variance, M_variance, specific_heat, suceptibility});

	return results;
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

	// Only count spins to the left and above, to avoid counting spin interactions twice
	// (saves some computing power compared to dividing total energy by two)
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

	// When calculating the local sum of surrounding energies, we count in all four directions
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

// Calculate the total magnetization (sums all spins in the system)
double M(mat spins, int L){
	double M_count = 0;
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			M_count += spins(i, j);
		}
	}
	return M_count;
}

// Print the matrix
void printMat(mat a, int L){
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			cout << a(i,j) << "	";
		}
		cout << endl;
	}
}

/*
int main(){
	//cout << "How many MC cycles?" << endl;
	//cin >> n;
	int N = 50;
	vector<int> E_count;
	vector<int> flip_N;
	MonteCarloIsing(N, true, 1.0, 20, E_count, flip_N);

	for (int i = 0; i < E_count.size(); i++){
		cout << "E_count: " << E_count[i] << ", MC cycles: " << i << ", Num. of flips: " << flip_N[i] << endl;

	}
	return 0;
}
*/
