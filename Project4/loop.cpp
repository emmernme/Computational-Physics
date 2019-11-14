// Compile using:
// c++ loop.cpp -o loop.o -larmadillo -O3 -lomp -std=c++11
#include "Ising.cpp"

using namespace std;
using namespace arma;

void printResults(vector<double> results){
	string desc_map[] = { "<E>", "<E^2>", "<M>", "<M^2>", "<|M|>", "E-var", "M-var", "Spec. heat", "Sucept." };

	for (int i = 0; i < results.size(); i++){
		cout << desc_map[i] << ": " << results[i] << endl;
	}
}

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

	// Prepare data variables for counting energies and flips
	vector<int> E_count;
	vector<int> flip_N;

	// Run the MC Ising model and fetch the resulting values
	vector<double> results = MonteCarloIsing(N, true, T, L, E_count, flip_N);
	printResults(results);

	// Write E-count to file for plotting
	ofstream E_count_output;
	E_count_output.open("E_count.dat");
	for (int i = 0; i < E_count.size(); i++){
		E_count_output << E_count[i] << endl;
	}
	E_count_output.close();

	// Write flip-count to file for plotting
	ofstream flip_output;
	flip_output.open("Flips_N.dat");
	for (int i = 0; i < flip_N.size(); i++){
		flip_output << flip_N[i] << endl;
	}
	flip_output.close();

	return 0;
}
