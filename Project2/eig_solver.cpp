#include <iostream>
#include <tuple>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

// Find the eigenvalues for a given matrix
tuple<vec, mat> eig_solver(mat A, int n, int &k, int &l){
	// Set up our eigvec-matrix
	mat eigvec(n,n);

	// Setting initial values and tolerance
	k = 0;
	l = 0;
	double tol = 10e-8;
	double max_iterations = pow(n, 3);
	double max_element = max_offdiag(A, k, l, n);

	double iterations = 0;
	// Run the Jacobi rotation until we reach the max num of iterations or the max element is within our tolerance
	while (iterations < max_iterations && max_element > tol){
		// Rotate and change our matrix to the rotated one
		A = jacobi_rotate(A, k, l, n, eigvec);
		// Find the new max. offdiagonal element
		max_element = max_offdiag(A, k, l, n);
		iterations++;
	}

	cout << "Max: " << max_element << endl;
	cout << "Iterations run: " << iterations << endl;
	return make_tuple(A.diag(), eigvec);
}
