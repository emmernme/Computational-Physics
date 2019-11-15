// Compile using:
// mpiCC 2x2-grid-mpi.cpp -o 2x2-grid-mpi.o -larmadillo -O3  -std=c++11
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
	int max = 5e4;
	int step = max / 10;
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
		vector<double> results = MonteCarloIsing(i*10, false, T, L, false);
		cycles[i/step] = i;
		E[i/step] = results[0];
		M[i/step] = results[2];
	}

	wtime = MPI_Wtime() - wtime;
  	cout << "Elapsed time in seconds = " << wtime << endl;
	MPI_Finalize();


	if (rank == 0){
		ofstream output;
		output.open(filename);
		output << "N,<E>,<M>" << endl;
		output.close();
	}

	return 0;
}
