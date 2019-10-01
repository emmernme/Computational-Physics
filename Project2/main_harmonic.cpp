
// Compile: g++ -std=c++11 main_harmonic.cpp -o harmonic.o -larmadillo -lblas
#include <iostream>
#include <tuple>
#include <cmath>
#include <armadillo>
#include "jacobi_rotate.cpp"
#include "armadillo_eig_solver.cpp"
#include "max_offdiag.cpp"
#include "eig_solver.cpp"

using namespace std;
using namespace arma;

bool only_arma = true;
int n = 2000;
double omega = 0.05;
double rho_max = 100;
double rho_0 = 0;
double h = (rho_max-rho_0)/double(n+1);
double e = -1.0/(h*h);

double rho(int i){
	return rho_0 + h*(i+1);
}

// Diagonal elements
double di(int i){
	double rho_i = rho(i);
	double d = 2.0/(h*h) + (omega*omega)*pow(rho_i,2) + 1.0/rho_i;
 	return d;
}

// Main function
int main(){
	// Dimensionality of the matrix
	int k, l;

	// Read omega from terminal
	cout << "Omega: ";
	cin >> omega;

	// Set up the matrix as a tridiagonal matrix
	mat A(n,n, fill::zeros);
	A(0, 0) = di(0);
	A(0, 1) = A(n-1,n-2) = e;
	for (int i = 1; i < n-1; i++){
		A(i, i-1) = A(i, i+1) = e;
		A(i, i) = di(i);
	}

	cout << "n: " << n << ", rho(∞): " << rho_max << ", omega: " << omega << endl;

	// Find the eigenvalues using Armadillo
	vec arma_eigval;
	mat arma_eigvec;
	tie(arma_eigval, arma_eigvec) = armadillo_eig_solver(A); // std::tie unwraps a tuple
	cout << "Eigenvalue Arma: " << endl;
	for (int i = 0; i < 5; i++){
		cout << arma_eigval(i) << endl;
	}

	if (!only_arma){
		// Find the eigenvalues with Jacobi function
		vec eigval;
		mat eigvec;
		tie(eigval, eigvec) = eig_solver(A, n, k, l);	
		cout << "Eigenvalue Jacobi: " << endl;
		for (int i = 0; i < 5; i++){
			cout << eigval(i) << endl;
		}
	}
	return 1; //success
}
