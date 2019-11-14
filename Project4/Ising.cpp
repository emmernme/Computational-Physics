#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
#include <tuple>
#include <string>
#include "helpers.cpp"

using namespace std;
using namespace arma; // Unwraps Armadillo-functions

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
			M_current += 2*(-spin);
			E_current += 2*E_xy;
		}
		flip_N.push_back(flip_count);

		// Update expectation values
		E_sum += E_current;
		E_sqrd_sum += E_current*E_current;
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

	// Normalization factors
	double norm 	= 1/(double) N;
	double s_norm = 1/(double) (L*L);

	// Calculate the mean values
	double E_mean 			= E_sum * norm;
	double E_sqrd_mean 	= E_sqrd_sum * norm;
	double M_mean		= M_sum * norm;
	double M_sqrd_mean 	= M_sqrd_sum * norm;
	double M_abs_mean 	= M_abs_sum * norm;

	double E_variance 	= (E_sqrd_mean - E_mean*E_mean) * s_norm;
	double M_variance 	= (M_sqrd_mean - M_abs_mean*M_abs_mean) * s_norm;

	double specific_heat = E_variance / (T*T);
	double susceptibility = M_variance / T;

	// Normalize
	E_mean 		*= s_norm;
	M_mean 		*= s_norm;
	E_sqrd_mean *= s_norm;
	M_sqrd_mean *= s_norm;
	M_abs_mean 	*= s_norm;

	// Prepare results
	vector<double>results;
	results.insert(results.end(), {E_mean, E_sqrd_mean, M_mean, M_sqrd_mean, M_abs_mean, E_variance, M_variance, specific_heat, susceptibility});

	return results;
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
