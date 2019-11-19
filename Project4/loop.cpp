/*
*	Run the MC Ising model once with desired L, N, T
*	Compile using:
*	c++ loop.cpp -o loop.o -larmadillo -O3 -std=c++11
*/

#include "Ising.cpp"

using namespace std;
using namespace arma;

int main(){
	// Setting up initial values
	double T = 1;
	int N = 5e6;
	int L = 20;

	// Read in alternative values
	cout << "Grid dim (L) = ";
	cin >> L;
	cout << "Cycles (N) = ";
	cin >> N;
	cout << "Temp (T) = ";
	cin >> T;

	// Run the MC Ising model and fetch the resulting values
	vector<double> results = MonteCarloIsing(N, true, T, L, true);
	printResults(results);

	return 0;
}
