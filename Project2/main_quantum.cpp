
// Compile: g++ -std=c++11 main_quantum.cpp -o quantum.o -larmadillo -lblas
#include <string>
#include <set>
#include <tuple>
#include <iostream>
#include <cmath>
#include <armadillo>
#include "jacobi_rotate.cpp"
#include "armadillo_eig_solver.cpp"
#include "max_offdiag.cpp"
#include "eig_solver.cpp"

using namespace std;
using namespace arma;

bool only_arma = true;
// Set up the constants we will use
int n = 1200;
double pmax = 50;
double rho_0 = 0;
double h = (pmax-rho_0)/double(n+1);
double e = -1.0/(h*h);

// Calculates the new diagonal elements
double di(int i){
	double Vi = pow(rho_0 + h*(i+1),2);
	double d = 2.0/(h*h)+Vi;
	return d;
}

// Main function
int main(){
	cout << "n: " << n << ", rho(∞): " << pmax << endl;

	// Dimensionality of the matrix
	int k, l;

	// Set up the matrix as a tridiagonal matrix
	mat A(n,n, fill::zeros);
	A(0, 0) = di(0);
	A(0, 1) = A(n-1,n-2) = e;
		for (int i = 1; i < n-1; i++){
			A(i, i-1) = A(i, i+1) = e;
			A(i, i) = di(i);
	}

	// Find eigenvalues using armadillo
	vec arma_eigval;
	mat arma_eigvec;
	tie(arma_eigval, arma_eigvec) = armadillo_eig_solver(A); // std::tie unwraps a tuple
	cout << "Eigenvalues Arma:" << endl;
	for (int i = 1; i < 5; i++){ // Print the eigvals (except first index, that's incorrect)
		cout << arma_eigval(i) << endl;
	}

	if (!only_arma){
		// Find eigenvalues using our Jacobi-solver
		vec eigval;
		mat eigvec;
		tie(eigval, eigvec) = eig_solver(A, n, k, l);
		cout << "Eigenvalues Jacobi:" << endl;
		for (int i = 0; i < 5; i++){
			cout << eigval(i) << endl;
		}
	}

	return 1; //success
}
