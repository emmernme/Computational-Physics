// Compile using:
// mpicxx phase_transitions_mpi.cpp -o phase_transitions_mpi.o -larmadillo -O3  -std=c++11
// Run using:
// mpirun -np 4 ./phase_transitions_mpi.o out

#include "Ising.cpp"
#include <iostream>
#include <mpi.h>

// Requirements: OpenMP ("brew install libomp" + "lomp" compiler flag)
#include <omp.h>

using namespace std;
using namespace arma;

int main(int argc, char * argv[]){
	// Setting up initial values and linear spacing of T
	double T0 = 2;
	double Tmax = 2.3;
	int n = 40;
	double dT = (Tmax-T0)/(double) n;
	int N = 1e9;

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

	int numprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int no_intervals = n/numprocs;
	int rank_begin = rank*no_intervals + 1;
	int rank_end = (rank + 1) * no_intervals;
	if ((rank == numprocs-1) && (rank_end < n)) rank_end = n;

	double wtime = MPI_Wtime();
	for (int i = 0; i < 4; i++){
		for (int k = rank_begin; k <= rank_end; k++){
			vector<double> results = MonteCarloIsing(N, true, T[k], L[i]);
			E_mean(i,k)        = results[0];
			M_abs_mean(i,k)    = results[4];
			specific_heat(i,k) = results[7];
			suceptibility(i,k) = results[8];
		}
	}

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
			for (int i = 0; i < 4; i++){
				values_output << "L: " << L[i] << setw(3) << setprecision(4) << setw(15) << E_mean(i,k) << setw(15);
				values_output << setprecision(4) << M_abs_mean(i,k) << setw(15);
				values_output << setprecision(4) << specific_heat(i,k);
				values_output << setw(15) << setprecision(4) << suceptibility(i,k) << endl;
			}
			values_output << endl;
		}
		values_output.close();
	}

	MPI_Finalize();

	return 0;
}
