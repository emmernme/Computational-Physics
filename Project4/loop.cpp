// Compile using:
// c++ loop.cpp -o loop.o -larmadillo -O3 -lomp -std=c++11
#include "Ising.cpp"

using namespace std;
using namespace arma;

int main(){
	// Setting up initial values
	double T = 1;
	int N = 5e6;
	int L = 20;

	cout << "Grid dim (L) = ";
	cin >> L;
	cout << "Cycles (N) = ";
	cin >> N;
	cout << "Temp (T) = ";
	cin >> T;

	// Run the MC Ising model and fetch the resulting values
	vector<double> results = MonteCarloIsing(N, true, T, L, true);
	printResults(results);

/*
	// Write flip-count to file for plotting
	ofstream flip_output;
	flip_output.open("Flips_N.dat");
	for (int i = 0; i < flip_N.size(); i++){
		flip_output << flip_N[i] << endl;
	}
	flip_output.close();
*/
	return 0;
}
