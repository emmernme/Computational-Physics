/*
*	Main file for project 1
*	Collaborators: Benedicte Allum Pedersen, Fredrik Forr, Emil Broll
*/
#include <iostream>	// Input/output
#include <cmath>	// Math functions
#include <cstdlib>	// atof function 
#include <fstream>	// File stream
#include <string>

using namespace std; // Unwraps lots of stuff

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
double f(double x){
	return 100*exp(-10 * x);
}

int main (int argc, char* argv[]){
	/*
	argv[] = {
		0 = main.cpp
		1 = n
		2 = matrix file - line 1: b, line 2: a, line 3: c
	}
	*/
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

	int n = atoi(argv[1]);
	double h = 1/(double)(n+1);

	double *b = new double[n];
	double *b_tilde = new double[n];
	double *g = new double[n];
	double *g_tilde = new double[n];
	double *a = new double[n-1];
	double *c = new double[n-1];
	double *u = new double[n];

	// Get data from file
	/* string line;
	getline(input, line);
	string_to_double_array(line, b);
	getline(input, line);
	string_to_double_array(line, a);
	getline(input, line);
	string_to_double_array(line, c);
	*/
	// Make random matrices
	srand (time(NULL));
	for (int i = 0; i < n-1; i++){
		a[i] = (double)(rand() % 100) / 100;
		cout << a[i] << "	";
	}
	cout << endl;
	for (int i = 0; i < n; i++){
		b[i] = (double)(rand() % 100) / 100;
		cout << b[i] << "	";
	}
	cout << endl;
	for (int i = 0; i < n-1; i++){
		c[i] = (double)(rand() % 100) / 100;
		cout << c[i] << "	";
	}
	cout << endl;


	b_tilde[0] = b[0];
	for (int i = 0; i < n; i++){
		g[i] = h*h * f(i*h);
	}

	g_tilde[0] = g[0];
	u[0] = u[n] = 0;

	// Forward substitution
	for (int i = 1; i < n; i++){
		b_tilde[i] = b[i] - (c[i-1] * a[i-1]) / b_tilde[i-1];
		g_tilde[i] = g[i] - (g_tilde[i-1] * a[i-1]) / b_tilde[i-1];
	}

	// Backward substitution
	for (int i = n-1; i >= 0; i--){
		u[i] = g_tilde[i] - (a[i] * u[i+1]) / b_tilde[i];
	}
    /* PRINT VALUES
	cout << endl;

	for (int i = 0; i < n; i++){
		cout << b_tilde[i] << "	";
	}
	cout << endl;

	for (int i = 0; i < n; i++){
		cout << g[i] << "	";
	}
	cout << endl;
	for (int i = 0; i < n; i++){
		cout << g_tilde[i] << "	";
	}
	cout << endl;
	*/

	for (int i = 0; i < n; i++){
		cout << u[i] << "	";
	}
	cout << endl;
	for (int i = 0; i < n; i++){
		double test = 1 - (1 - exp(-10)) * i*h - exp(-10 * i*h);
		cout << test << "	";
	}



	return 0; // Success
}
