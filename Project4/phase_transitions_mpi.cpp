// Compile using:
// mpicxx phase_transitions_mpi.cpp -o phase_transitions_mpi.o -larmadillo -O3  -std=c++11
// Run using:
// mpirun -np 4 ./phase_transitions_mpi.o out

#include "Ising.cpp"
#include "ProgressBar.hpp"
#include <iostream>
#include <mpi.h>

using namespace std;
using namespace arma;

int main(int argc, char * argv[]){
	// Initial values
	const int n = 19; // Number of temperature steps -1
	int N = 1e7; // Number of MC cycles
	const int L[4] = {40, 60, 80, 100}; // Dimensions
	const int l = 4; // Number of different sizes

	// Setting up initial values and linear spacing of T
	vector<double> T;
	double T0 = 2.0;
	double Tmax = 2.8;
	double dT = (Tmax-T0)/(double) n;
	for (int i = 0; i <= n; i++){
		T.push_back(T0+i*dT);
	}

	// Set up MPI for parallelization
	int numprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set up local matrices for current process
	double local_E_mean[l][n+1] = {0};
	double local_M_abs_mean[l][n+1] = {0};  
	double local_specific_heat[l][n+1] = {0};
	double local_suceptibility[l][n+1] = {0};

	// Divide up the temperatures intervals between the processors
	int no_intervals = (n+1)/numprocs;
	int rank_begin = rank*no_intervals;
	int rank_end = ((rank + 1) * no_intervals) - 1;
	if ((rank == numprocs-1) && (rank_end < n)) rank_end = n;

	// Set up a progress bar
	ProgressBar progressBar(l*(n+1), 80);

	double wtime = MPI_Wtime();
	for (int i = 0; i < l; i++){ // Loop over the dimensions
		for (int k = rank_begin; k <= rank_end; k++){ // Loop over the temperatures
			vector<double> results = MonteCarloIsing(N, false, T[k], L[i]);

			// Populate our local results
			local_E_mean[i][k]        = results[0];
			local_M_abs_mean[i][k]    = results[l];
			local_specific_heat[i][k] = results[7];
			local_suceptibility[i][k] = results[8];

			++progressBar;
			progressBar.display();
		}
	}
	progressBar.done();
	
	// Set up the global results matrices
	double E_mean[l][n+1] = {0};
	double M_abs_mean[l][n+1] = {0};  
	double specific_heat[l][n+1] = {0};
	double suceptibility[l][n+1] = {0};

	// "Merge" the local results into the global matrices
	for (int i = 0; i < l; i++){
		MPI_Reduce(&local_E_mean[i], &E_mean[i], n+1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_M_abs_mean[i], &M_abs_mean[i], n+1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_specific_heat[i], &specific_heat[i], n+1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_suceptibility[i], &suceptibility[i], n+1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	}

	// Make sure all processes are finished before moving on
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0){
		wtime = MPI_Wtime() - wtime;
  		cout << "Elapsed time = " << wtime/60 << " min" << endl;

		// Write results to file
		ofstream values_output;
		values_output.open("phase_transitions.dat");
		values_output << endl << setw(20) << "E_mean"  << setw(15) <<  "M_abs_mean";
		values_output << setw(15) <<  "specific_heat" << setw(15) << "suceptibility" << endl;
		for (int k = 0; k <= n; k++){
			values_output << "T: " <<  T[k] << endl;;
			for (int i = 0; i < l; i++){
				values_output << "L: " << L[i] << setw(3) << setprecision(4) << setw(15) << E_mean[i][k] << setw(15);
				values_output << setprecision(4) << M_abs_mean[i][k] << setw(15);
				values_output << setprecision(4) << specific_heat[i][k];
				values_output << setw(15) << setprecision(4) << suceptibility[i][k] << endl;
			}
			values_output << endl;
		}
		values_output.close();
	}

	MPI_Finalize(); // Parallelization over

	return 0;
}
