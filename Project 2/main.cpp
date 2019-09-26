
//This file uses armadillo, compile using "<compiler> <filename> -larmadillo"

#include <iostream>
#include <cmath>
#include <armadillo>
#include "jacobi_rotate.cpp"
#include "armadillo_eig_solver.cpp"
#include "max_offdiag.cpp"
#include "eig_solver.cpp"

using namespace std;
using namespace arma;

// Main function
int main(){
	// Dimensionality of the matrix
	int n = 5;

	clock_t start,finish;


	// Set up the matrix as a tridiagonal matrix

	mat A(n,n, fill::zeros);
	A(0, 0) = A(n-1,n-1) = 2.0;
	A(0, 1) = A(n-1,n-2) = -1.0;
		for (int i = 1; i < n-1; i++){
			A(i, i-1) = A(i, i+1) = -1.0;
			A(i, i) = 2.0;
	}

	// Find the eigenvalues with armadillo function
	vec arma_eigval;
	mat arma_eigvec;

	//start timing for armadillo solver

	start = clock();
	tie(arma_eigval, arma_eigvec) = armadillo_eig_solver(A); // std::tie unwraps a tuple
	finish = clock();

	double t2 = (double (finish - start))/CLOCKS_PER_SEC;

	// Find the eigenvalues with our own solver
	vec eigval;
	mat eigvec;

	//Start clock for jacobi method

	start = clock();

	tie(eigval, eigvec) = eig_solver(A, n);

	finish = clock();
	double t1 = (double (finish- start)) /CLOCKS_PER_SEC;

	cout << "Jacobi: " << t1 << "seconds" << endl << eigvec << endl;
	cout << "Arma: " << t2 << "seconds" << endl << arma_eigvec << endl;

	return 1; //success
}
