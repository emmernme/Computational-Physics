/*
*	Main file for project 1
*	Collaborators: Benedicte Allum Pedersen, Fredrik Forr, Emil Broll
*/
// Requires Armadillo - compile like this: "c++ main.cpp -larmadillo"
#include <iostream>	// Input/output
#include <cmath>	// Math functions
#include <cstdlib>	// atof function
#include <fstream>	// File stream
#include <string>
#include <armadillo>

using namespace std; // Unwraps lots of stuff
using namespace arma; // Unwraps Armadillo-functions

void string_to_double_array(string text, double *arr, int offset);

double f(double x){
	return 100 * exp(-10 * x);
}

int main (int argc, char* argv[]){
/*	argv[] = {
		0 = main.cpp
		1 = n
		2 = matrix file - line 1: b, line 2: a, line 3: c
	}
	// Read arguments from file-functionality
	if (argc < 3){
		cout << "Not enough arguments (n, matrix file)" << endl;
		system("pause");
		return -1;
	}
	ifstream input(argv[2]);
	if (!input.is_open()){ // No such file
		cout << "Error opening output file" << endl;
		system("pause");
		return -1;
	}
	// Get data from file
	string line;
	getline(input, line);
	string_to_double_array(line, b);
	getline(input, line);
	string_to_double_array(line, a);
	getline(input, line);
	string_to_double_array(line, c);
	*/

	// Step size
	int n = atoi(argv[1]);
	double h = 1/(double)(n+1);

	// Initialize vectors
	double *b = new double[n];
	double *b_tilde = new double[n];
	double *g = new double[n];
	double *g_tilde = new double[n];
	double *a = new double[n-1];
	double *c = new double[n-1];
	double *v = new double[n];
	double *exact = new double[n];

	// Special case
	for (int i = 0; i < n; i++){
		b[i] = 2;
		if (i < n-1){
			a[i] = c[i] = -1;
		}
	}

	// Make random matrices
/*	srand (time(NULL));
	for (int i = 0; i < n; i++){
		b[i] = (double)(rand() % 100) / 100;
		if (i < n-1){
			a[i] = (double)(rand() % 100) / 100;
			c[i] = (double)(rand() % 100) / 100;
		}
	} */

	// Pre-calculate g-values (b_tilde in proj desc)
	for (int i = 0; i < n; i++){
		g[i] = h*h * f(i*h);
	}

	// Conditions
	b_tilde[0] = b[0];
	g_tilde[0] = g[0];
	v[0] = 0;

	/*
	*	Thomas Algorithm
	*/

	clock_t start, finish;
	start = clock();
	// Forward substitution
	for (int i = 1; i < n; i++){
		b_tilde[i] = b[i] - ((a[i-1] * c[i-1]) / b_tilde[i-1]);
		g_tilde[i] = g[i] - ((g_tilde[i-1] * a[i-1]) / b_tilde[i-1]);
	}
	// Backward substitution
	v[n-1] = g_tilde[n-1] / b_tilde[n-1];
	for (int i = n-2; i > 0; i--){
		v[i] = (g_tilde[i] - c[i] * v[i+1]) / b_tilde[i];
	}
	finish = clock();
	double t1 = (double (finish-start)) / CLOCKS_PER_SEC;


	/*
	*	Special case algorithm
	*/

	double *special_b_tilde = new double[n];
	double *special_g_tilde = new double[n];
	double *special_v = new double[n];
	special_b_tilde[0] = b[0];
	special_g_tilde[0] = g[0];

	start = clock();
	// Forward substitution
	for (int i = 1; i < n; i++){
		special_b_tilde[i] = 2 - (double)(i-1)/i;
		special_g_tilde[i] = g[i] + special_g_tilde[i-1] / special_b_tilde[i-1];
	}
	// Backward substitution
	special_v[n-1] = special_g_tilde[n-1] / special_b_tilde[n-1];
	for (int i = n-2; i > 0; i--){
		special_v[i] = (special_g_tilde[i] + special_v[i+1]) / special_b_tilde[i];
	}
	finish = clock();
	double tspecial = (double (finish-start)) / CLOCKS_PER_SEC;

	cout << "Backward and forward substitution took " << t1 << " seconds." << endl;
	cout << "Special case took " << tspecial << " seconds." << endl;

	if (n < 1001){
	/*
	*	Armadillo LU-decompositon solving
	*/

	// Make arma-compatible vectors
	vec arma_g(n);
	mat L, U, P;
	vec u_arma;
	mat A = mat(n,n); // nxn-matrix
	for (int i = 0; i < n; i++){
		arma_g(i) = g[i];
	}

	// Prepare the matrix
	A(0, 0) = A(n-1,n-1) = 2;
	A(0, 1) = A(n-1,n-2) = -1;
	for (int i = 1; i < n-1; i++){
		A(i, i-1) = A(i, i+1) = -1;
		A(i, i) = 2;
	}

	start = clock();
	lu(L, U, P, A);
	solve(u_arma, (L*U), arma_g);
	finish = clock();
	double t2 = (double (finish - start)) / CLOCKS_PER_SEC;

	cout << "LU decomposition using Armadillo took " << t2 << " seconds." << endl;


	// Save results to file, but not for large n-values
		ofstream output;
		output.open("n_" + to_string(n) + ".dat");
		for (int i = 0; i < n; i++){
			exact[i] = 1 - (1 - exp(-10)) * i*h - exp(-10 * i*h);

			output << v[i] << "," << exact[i] << endl;
		}
		output.close();
	}

	// Calculate relative error
	double max_error = 0;
	for (int i = 1; i < n; i++){
		double error = log10( abs( (v[i] - exact[i])/exact[i] ) );
		if (error > max_error) max_error = error;
	}
	cout << "Max error: " << max_error << endl;

	// Memory cleanup
	delete[] b;
	delete[] b_tilde;
	delete[] g;
	delete[] g_tilde;
	delete[] a;
	delete[] c;
	delete[] v;
	delete[] exact;
	delete[] special_b_tilde;
	delete[] special_g_tilde;
	delete[] special_v;

	return 0; // Success
}

// Function to split input from file directly into an array
void string_to_double_array(string text, double *arr, int offset = 0){
	// Split at spaces
	int i = offset;
	size_t last, next = 0;
	while ((next = text.find(" ", last)) != string::npos) {
		arr[i] = atof(text.substr(last, next-last).c_str());
		last = next + 1;
		i++;
	}
	// Last element:
	arr[i] = atof(text.substr(last).c_str());
}