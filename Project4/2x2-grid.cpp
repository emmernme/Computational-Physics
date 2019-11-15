// Compile using:
// c++ loop.cpp -o loop.o -larmadillo -O3 -lomp -std=c++11
#include "Ising.cpp"
#include <omp.h>

using namespace std;
using namespace arma;

int main(){
	// Setting up constants
	double T = 1.0;
	int L = 2;

	ofstream output;
	output.open("MC_cycles_mean_E+M_T=1.dat");
	output << "N,<E>,<M>" << endl;

	int thread_num = omp_get_max_threads();
	omp_set_num_threads(thread_num);
	cout << "The number of processors available = " << omp_get_num_procs() << endl;
	cout << "The number of threads available    = " << thread_num <<  endl;
	// defining time and various variables needed for the integration
	double wtime = omp_get_wtime();

	int max = 5e4;
	int step = max / 10;
	int N = max / step;

	int cycles[N];
	double E[N];
	double M[N];

	int i;
	#pragma omp parallel for
	for (i = 1; i <= 5e3; i++){
		vector<double> results = MonteCarloIsing(i*10, false, T, L, false);
		cycles[i/step] = i*10;
		E[i/step] = results[0];
		M[i/step] = results[2];
	}
	wtime = omp_get_wtime() - wtime;
  	cout << "Elapsed time in seconds = " << wtime << endl;

	output.close();
	return 0;
}
