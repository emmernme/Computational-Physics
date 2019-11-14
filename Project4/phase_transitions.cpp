// Compile using:
// c++ phase_transitions.cpp -o phase_transitions.cpp -larmadillo -O3 -lomp -std=c++11
#include "Ising.cpp"

// Requirements: OpenMP ("brew install libomp clang-omp" + "lomp" compiler flag)
#include <omp.h>

using namespace std;
using namespace arma;

int main(){
	//setting up initial values and linear spacing of T
	double T0 = 1;
	double Tmax = 3;
	int n = 10;
	double dT = (Tmax-T0)/(double) n;
	int N = 5e6;


	double *T = new double[n];
	//int L[4] = {40, 60, 80, 100};
	int L = 20;
	/*
	mat E_mean       (4, n-1, fill::zeros);
	mat E_sqrd_mean  (4, n-1, fill::zeros);
	mat M_mean       (4, n-1, fill::zeros);
	mat M_sqrd_mean  (4, n-1, fill::zeros);
	mat M_abs_sum    (4, n-1, fill::zeros);
	mat E_variance   (4, n-1, fill::zeros);
	mat M_variance   (4, n-1, fill::zeros);
	mat specific_heat(4, n-1, fill::zeros);
	mat suceptibility(4, n-1, fill::zeros);
	*/

	for(int i = 0; i < n; i++){
	T[i] = T0+i*dT;
	}
	/*
	for (int i = 0; i < 4; i++){
		for (int k = 0; k < n-1; k++){

		}
	}
	*/

	vector<int> E_count;
	vector<int> flip_N;
	cout << "Grid dim (L) = ";
	cin >> L;
	cout << "Cycles (N) = ";
	cin >> N;
	cout << "Temp (T) = ";
	cin >> T0;

	vector<double> results = MonteCarloIsing(N, true, T0, L, E_count, flip_N);

	double E_mean        = results[0];
	double E_sqrd_mean   = results[1];
	double M_mean        = results[2];
	double M_sqrd_mean   = results[3];
	double M_abs_sum     = results[4];
	double E_variance    = results[5];
	double M_variance    = results[6];
	double specific_heat = results[7];
	double suceptibility = results[8];

	printResults(results);


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
  E_count_output.close();
*/
  ofstream E_count_output;
  E_count_output.open("E_count.dat");
  for(int i = 0; i < E_count.size(); i++){
    E_count_output << E_count[i] << endl;
  }
  E_count_output.close();

	ofstream flip_output;
	flip_output.open("Flips_N.dat");
	for (int i = 0; i < flip_N.size(); i++){
		flip_output << flip_N[i] << endl;
	}
  flip_output.close();


	/*
	cout << setw(20) << "E_mean" << setw(15) << "     E_sqrd_mean" << setw(15);
	cout << "M_mean" << setw(15) << "M_sqrd_mean" << setw(15) << "M_abs_sum";
	cout << setw(15) << "E_variance" << setw(15) << "M_variance" << setw(15);
	cout << "specific_heat" << setw(15) << "suceptibility" << endl;
	for(int i = 0; i < 4; i++){
	for(int k = 0; k < n-1; k++){
		cout << "T: " <<  T[i] << setprecision(4) << setw(15) << E_mean(i,k) << setw(15);
		cout << setprecision(4) << E_sqrd_mean(i,k) << setw(15);
		cout << setprecision(4) << M_mean(i,k) << setw(15) << M_sqrd_mean(i,k) << setw(15);
		cout << setprecision(4) << M_abs_sum(i,k) << setw(15);
		cout << setprecision(4) << E_variance(i,k) << setw(15);
		cout << setprecision(4) << M_variance(i,k) << setw(15);
		cout << setprecision(4) << specific_heat(i,k);
		cout << setw(15) << setprecision(4) << suceptibility(i,k) << endl;
	}
	}
	*/

return 0;
}
