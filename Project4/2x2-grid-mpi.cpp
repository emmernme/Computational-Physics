// Compile using:
// mpicxx 2x2-grid-mpi.cpp -o 2x2-grid-mpi.o -larmadillo -O3  -std=c++11
// Run using:
// mpirun -np 4 ./2x2-grid-mpi.o out
#include "Ising.cpp"
#include <mpi.h>

using namespace std;
using namespace arma;

int main(int argc, char * argv[]){
	// Setting up constants
	string filename = "MC_cycles_mean_E+M_T=1.dat";
	int numprocs, rank;

	double T = 1.0;
	int L = 2;

	int max = 1e5;
	int step = 1;
	int N = max / step;

	int cycles[N];
	double E[N];
	double M[N];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	

	int no_intervals = N/numprocs;
	int rank_begin = rank*no_intervals + 1;
	int rank_end = (rank + 1) * no_intervals;
	if ((rank == numprocs-1) && (rank_end < N)) rank_end = N;


	double wtime = MPI_Wtime();

	for (int i = rank_begin; i <= rank_end; i++){
		vector<double> results = MonteCarloIsing((i+1)*step, false, T, L, false);
		cycles[i] = (i+1)*step;
		E[i] = results[0];
		M[i] = results[2];
	}


	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0){
		wtime = MPI_Wtime() - wtime;
  		cout << "Elapsed time in seconds = " << wtime << endl;
		ofstream output;
		output.open(filename);
		output << "N,<E>,<M>" << endl;
		for (int j = 0; j < N; j++){
			output << cycles[j] << "," << E[j] << "," << M[j] << endl;
		}
		output.close();
	}

	MPI_Finalize();

	return 0;
}
