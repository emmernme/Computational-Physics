/*
*	Helper functions
* 	Calculating energies, magnetization
*	Printing a matrix, and printing results
*/

// Fill a spin matrix
void fill_spins(mat &spins, int L, bool random){
	spins = mat(L,L);
	if (random){
		random_device seeder;
		mt19937 engine(seeder());
		uniform_real_distribution<double> dist(0, 1);

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
}

// Calculate the contribution of the spins above and left of a given position
int E_i_minimal(mat spins, int x, int y, int L){
	// Only count spins to the left and above, to avoid counting spin interactions twice
	// (saves some computing power compared to dividing total energy by two)
	int E_count = 0;
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
	return -E_count;
}

// Calculate the contribution of a single spin and all of its surroundings to the total energy
int E_i(mat spins, int x, int y, int L){
	int E_count = 0;
	// When calculating the local sum of surrounding energies, we count in all four directions
	E_count -= E_i_minimal(spins, x, y, L);

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
// Calculate the total energy of the system
int E_tot(mat spins, int L){
	int E_count = 0;
	// Loop over all the individual spins' energy contributions
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			E_count += E_i_minimal(spins, i, j, L);
		}
	}
	return E_count;
}

// Calculate the total magnetization (sums all spins in the system)
int M(mat spins, int L){
	int M_count = 0;
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

// Print the result-vector with descriptive prefixes
void printResults(vector<double> results){
	string desc_map[] = { "<E>", "<E^2>", "<M>", "<M^2>", "<|M|>", "E-variance", "M-variance", "Specific heat", "Suceptibility", "Flip factor" };
	for (int i = 0; i < results.size(); i++){
		cout << desc_map[i] << ": " << results[i] << endl;
	}
}
