// Compile using:
// c++ phase_transitions.cpp -o phase_transitions.o -larmadillo -O3 -lomp -std=c++11
#include "Ising.cpp"
#include <iostream>

// Requirements: OpenMP ("brew install libomp" + "lomp" compiler flag)
#include <omp.h>

using namespace std;
using namespace arma;

int main(){
	// Setting up initial values and linear spacing of T
	double T0 = 2;
	double Tmax = 2.3;
	int n = 10;
	double dT = (Tmax-T0)/(double) n;
	int N = 20;


	vector<double> T;
	int L[4] = {40, 60, 80, 100};

	mat E_mean       (4, n+1, fill::zeros);
	mat M_abs_mean   (4, n+1, fill::zeros);
	mat specific_heat(4, n+1, fill::zeros);
	mat suceptibility(4, n+1, fill::zeros);

	vector<int> E_count;
	vector<int> flip_N;

	for(int i = 0; i <= n; i++){
		T.push_back(T0+i*dT);
	}

// PARRRAALLLLELLLLIIIIIIIIZE

	for (int i = 0; i < 4; i++){
		for (int k = 0; k <= n; k++){
			vector<double> results = MonteCarloIsing(N, true, T[k], L[i]);
			E_mean(i,k)        = results[0];
			M_abs_mean(i,k)    = results[4];
			specific_heat(i,k) = results[7];
			suceptibility(i,k) = results[8];
		}
	}

	//printResults(results);


	/*std::map<int, int> energy_counter;
	for (auto const &value : E_count){
		energy_counter[value]++;
	}
	for (auto const &energy : energy_counter){
		cout << "Energy " << energy.first() << "repeats " << energy.second() << " times." << endl;

	}*/
/*
	std::map<int, int> energies;

    for (auto const &energy : E_count){
        energies[energy]++;
	}

	ofstream E_count_output;
	E_count_output.open("E_count.dat");
    for (auto const &b : energies){
		E_count_output << b.first << "," << b.second << endl;
	}
*/

	ofstream values_output;
	values_output.open("phase_transitions.dat");
	values_output << endl << setw(20) << "E_mean"  << setw(15) <<  "M_abs_mean";
	values_output << setw(15) <<  "specific_heat" << setw(15) << "suceptibility" << endl;
	for(int k = 0; k <= n; k++){
		values_output << "T: " <<  T[k] << endl;;
		for(int i = 0; i < 4; i++){
			values_output << "L: " << L[i] << setw(3) << setprecision(4) << setw(15) << E_mean(i,k) << setw(15);
			values_output << setprecision(4) << M_abs_mean(i,k) << setw(15);
			values_output << setprecision(4) << specific_heat(i,k);
			values_output << setw(15) << setprecision(4) << suceptibility(i,k) << endl;
		}
		values_output << endl;
	}
	values_output.close();

return 0;
}
