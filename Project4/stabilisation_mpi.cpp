// Compile using:
// mpicxx stabilisation.cpp -o stabilisation.o -larmadillo -O3  -std=c++11
// Run using:
// mpirun -np 4 ./stabilisation.o out

#include "Ising.cpp"
#include "ProgressBar.hpp"
#include <iostream>
#include <mpi.h>

using namespace std;
using namespace arma;

int main(int argc, char * argv[]){
	// Initial values
	const int n = 100; // Number of cycle steps -1
	const int L = 20; // Dimension
	const int T = 1.0; // Temp

	// Setting up initial values and linear spacing of T
	vector<double> MC;
	double MC0 = 1e2;
	double MCmax = 1e6;
	double dMC = (MCmax-MC0)/(double) n;
	for (int i = 0; i <= n; i++){
		MC.push_back(MC0+i*dMC);
	}

	// Set up MPI for parallelization
	int numprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// Set up local matrices for current process
	double local_E_mean[n+1] = {0};
	double local_M_abs_mean[n+1] = {0};  

	// Divide up the temperatures intervals between the processors
	int no_intervals = (n+1)/numprocs;
	int rank_begin = rank*no_intervals;
	int rank_end = ((rank + 1) * no_intervals) - 1;
	if ((rank == numprocs-1) && (rank_end < n)) rank_end = n;

	// Set up a progress bar
	ProgressBar progressBar((n+1), 80);

	double wtime = MPI_Wtime();
	for (int k = rank_begin; k <= rank_end; k++){ // Loop over the temperatures
		vector<double> results = MonteCarloIsing(MC[k], false, T, L);

		// Populate our local results
		local_E_mean[k]        = results[0];
		local_M_abs_mean[k]    = results[2];

		++progressBar;
		progressBar.display();
	}
	progressBar.done();
	
	// Set up the global results matrices
	double E_mean[n+1] = {0};
	double M_abs_mean[n+1] = {0};  

	// "Merge" the local results into the global matrices
	MPI_Reduce(&local_E_mean, &E_mean, n+1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_M_abs_mean, &M_abs_mean, n+1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	// Make sure all processes are finished before moving on
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0){
		wtime = MPI_Wtime() - wtime;
  		cout << "Elapsed time = " << wtime/60 << " min" << endl;

		// Write results to file
		ofstream output;
		output.open("stabilisation.dat");

		for (int k = 0; k <= n; k++){
			output << "N,<E>,<M>" << endl;
			for (int i = 0; i <= n; i++){
				output << MC[i] << "," << E_mean[i] << "," << M_abs_mean[i] << endl;
			}
		}
		output.close();
	}

	MPI_Finalize(); // Parallelization over

	return 0;
}
