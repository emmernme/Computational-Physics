/*
Possible tests:

- Check randomness of the random numbers
- Check that the local energies are always -4, -2, 0, 2, 4
- Check that global energies are always a multiple of the values in our table
- Check that the energy in our not-random matrix is always xxx
- Check that the magnetization in our not-random matrix is always L*L
*/

#define CATCH_CONFIG_MAIN

#include "External/catch.hpp"
#include "Ising.cpp"

TEST_CASE("Testing the magnetization of a non-random matrix"){
	// Set up system
	int L = 20;
	mat spins;
	fill_spins(spins, L, false);

	// Exact value
	double exact = 20*20;
	double calculated = M(spins, L);
	REQUIRE(calculated == Approx(exact).epsilon(0.0001));
}

TEST_CASE("Testing the local energies in a random matrix"){
	// Set up system
	int L = 20;
	mat spins;
	fill_spins(spins, L, true);
	vector<int> possible_energies = {-4, -2, 0, 2, 4};

	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			REQUIRE_THAT(possible_energies, Catch::VectorContains(E_i(spins, i, j, L)));
		}
	}
}

TEST_CASE("Testing the Ising model results for <E>, <E^2>, <M>, <M^2>, <|M|>, <|M|^2>"){
	// Setting up initial values
	double T = 1.0;
	int N = 2e8;
	int L = 2;

	// Run the MC Ising model and fetch the resulting values
	vector<double> results = MonteCarloIsing(N, false, T, L);
	// {E_mean, E_sqrd_mean, M_mean, M_sqrd_mean, M_abs_mean, E_variance, M_variance, specific_heat, susceptibility, flip_factor}
	
	vector<double> exactResults = { -1.9960, 15.968, 0, 3.9933, 0.9987 };
	
	REQUIRE(results[0] == Approx(exactResults[0]).epsilon(0.0001));
	REQUIRE(results[1] == Approx(exactResults[1]).epsilon(0.0001));
	REQUIRE(results[2] == Approx(exactResults[2]).epsilon(0.005)); // Lower precision because of highly fluctuating magnetization
	REQUIRE(results[3] == Approx(exactResults[3]).epsilon(0.0001));
	REQUIRE(results[4] == Approx(exactResults[4]).epsilon(0.0001));
}