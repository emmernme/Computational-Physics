/*
*	Helper functions
*/

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

// Print the result-vector with descriptive prefixes
void printResults(vector<double> results){
	string desc_map[] = { "<E>", "<E^2>", "<M>", "<M^2>", "<|M|>", "E-var", "M-var", "Spec. heat", "Sucept." };

	for (int i = 0; i < results.size(); i++){
		cout << desc_map[i] << ": " << results[i] << endl;
	}
}
