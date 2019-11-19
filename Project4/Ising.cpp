/*
*	Main Ising Model Monte Carlo file
*	Function MonteCarloIsing takes the input:
*		N: number of MC cycles to run
*		random: whether to initialize the spins randomly or not
*		T: the temperature of the lattice
*		L: the dimension of the lattice
*		count_E: whether to count each E [currently disabled for speed]
*	Results in a vector with the following elements:
*		{E_mean, E_sqrd_mean, M_mean, M_sqrd_mean, M_abs_mean, E_variance, M_variance, specific_heat, susceptibility, flip_factor}
*/
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
#include <tuple>
#include <string>

using namespace std;
using namespace arma; // Unwraps Armadillo-functions
#include "helpers.cpp"

vector<double> MonteCarloIsing(int N, bool random, double T, int L, bool count_E = false){
	// Constants
	double beta = 1 / T; //  / (k_b * T);

	// Set up an array of possible \Delta E transition values, delta_E = {-8, -4, 0, 4, 8};
	map<int, double> E_trans = {
	// 	{energy, transition probability}
		{-4, exp(-beta * 8)},
		{-2, exp(-beta * 4)},
		{0, 1.0},
		{2, 1.0}, //exp(-beta * -4)},
		{4, 1.0}, //exp(-beta * -8)},
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

	// Prepare summation variables (PS: double because of integer overflow!)
	double E_sum = 0;
	double E_sqrd_sum = 0;
	double M_sum = 0;
	double M_sqrd_sum = 0;
	double M_abs_sum = 0;

	// Set up the initial magnetisation and energy
	double M_current = M(spins, L);
	double E_current = E_tot(spins, L);

	int flip_count = 0; // Number of accepted flips

	// vector<int> E_counter;

	// Monte Carlo-loop
	for (int i = 1; i <= N; i++){
		int x = (int) (pos(engine) + 0.5); // Random position in the lattice
		int y = (int) (pos(engine) + 0.5); // Random position in the lattice

		// Calculate the surrounding energy contributions
		int E_xy = E_i(spins, x, y, L);

		// Metropolis algo
		// Flip spin if (transition probability = 1) or random number [0,1] is <= transition probability
		double P = E_trans[E_xy];
		if (P == 1 || dist(engine) <= P){
			flip_count++; // Count each flip

			// Flip the spin
			int spin = -spins(x,y);
			spins(x,y) = spin;

			// Calc new local energy and total energy
			E_xy = -E_xy; // Flipping centre spin inverses the energy
			M_current += 2*(spin);
			E_current += 2*E_xy;
		}

		// Update expectation values
		E_sum += E_current;
		E_sqrd_sum += E_current*E_current;
		M_sum += M_current;
		M_sqrd_sum += M_current*M_current;
		M_abs_sum += abs(M_current);

		// Count energies to make probability - after 10 % of cycles have completed
		// COMMENTED FOR PERFORMANCE WHEN RUNNING LARGE SAMPLES
		/* if (count_E && (i > 0.1 * N)){
			E_counter.push_back(E_current);
		} */
	}

	// If we're counting E's, save to file
	/* if (count_E){
		ofstream E_count_output;
		E_count_output.open("E_count.dat");
		for (int i = 0; i < E_counter.size(); i++){
			E_count_output << E_counter[i] << endl;
		}
		E_count_output.close();
	} */

	// Normalization factors
	double norm 	= 1/(double) N; // Per cycle
	double s_norm 	= 1/(double) (L*L); // Per spin

	// Calculate the mean values
	double E_mean 		= E_sum * norm;
	double E_sqrd_mean 	= E_sqrd_sum * norm;
	double M_mean		= M_sum * norm;
	double M_sqrd_mean 	= M_sqrd_sum * norm;
	double M_abs_mean 	= M_abs_sum * norm;

	// Calculate other interesting quantities
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

	// Flips per MC cycle
	double flip_factor = (double) flip_count / (double) N;

	// Prepare results
	vector<double>results;
	results.insert(results.end(), {E_mean, E_sqrd_mean, M_mean, M_sqrd_mean, M_abs_mean, E_variance, M_variance, specific_heat, susceptibility, flip_factor});
	return results;
}