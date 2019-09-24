
//This file uses armadillo, compile using "<compiler> <filename> -larmadillo"

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;


// Test function for armadillo diagonalization tool.
tuple<vec, mat> armadillo_eig_solver(mat A){
	vec eigval;
	mat eigvec;

	eig_sym(eigval, eigvec, A);

	return make_tuple(eigval, eigvec); // std::tuple can contain different data types
}

// Function for solving with jacobi's method
mat jacobi_rotate(mat A, int k, int l, int n, mat &eigvec){

	double s, c; // sin, cos

	// Skip some calculations if a_kl = 0
	if (A(k,l) == 0){
		s = 0.0;
		c = 1.0;
	} else {
		double t, tau;
		tau = (A(l,l) - A(k,k))/2*A(k,l);

		// Not sure what this does
		if (tau >= 0){
			t = - tau + sqrt(1.0+ tau*tau);
		} else {
			t = - tau - sqrt(1.0+ tau*tau);
		}

		// Calculate cos, sin
		c = 1.0/sqrt(1.0 + t*t);
		s = t * c;
	}
	cout << "k: " << k << ", l: " << l << endl;

	// Set up the new matrix and the max values (of the old matrix)
	mat B(n,n);
	B(0,0) = A(0,0);
	B(k, k) = A(k,k)*pow(c,2)-2.0*A(k,l)*c*s + A(l,l)*pow(s,2);
	B(l, l) = A(l,l)*pow(c,2)+2.0*A(k,l)*c*s + A(k,k)*pow(s,2);
	B(k, l) = B(l, k) = 0.0;
	// Make mat holders for our eigvecs

	// Set the non-diagonal elements for each row
	for (int i = 0; i < n; i++){
		if (i != k && i!= l){
			B(i, k) = A(i,k)*c - A(i,l)*s;
			B(i, l) = A(i,l)*c + A(i,k)*s;
			B(k, i) = B(i,k);
			B(l, i) = B(i,l);
		}
		// Set the new eigenvectors
		eigvec(i,k) = c * eigvec(i,k) - s * eigvec(i,l); 
		eigvec(i,l) = c * eigvec(i,l) + s * eigvec(i,k);
		// not sure why/how, but whatever.

	}
	return B;
}


// Finds the maximum value and its index in the matrix
double max_offdiag(mat A, int &k, int &l, int n){
	double maxarg = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i != j && fabs(maxarg) < fabs(A(i,j))){
				maxarg = fabs(A(i,j));
				k = i;
				l = j;
			}
		}
	}
	return maxarg;
}

// Find the eigenvalues for a given matrix 
tuple<vec, mat> eig_solver(mat A, int n){
	// Set up our eigvec-matrix
	mat eigvec;

	// Setting initial values and tolerance
	int k = 0;
	int l = 0;
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

// Main function
int main() {
	// Dimensionality of the matrix
	int n = 10;

	// Set up the matrix as a tridiagonal matrix
	mat A(n,n);
	A(0, 0) = A(n-1,n-1) = 2;
	A(0, 1) = A(n-1,n-2) = -1;
	for (int i = 1; i < n-1; i++){
		A(i, i-1) = A(i, i+1) = -1;
		A(i, i) = 2;
	}

	// Find the eigenvalues with armadillo functions
	vec arma_eigval;
	mat arma_eigvec;
	tie(arma_eigval, arma_eigvec) = armadillo_eig_solver(A); // std::tie unwraps a tuple

	// Find the eigenvalues with our own solver
	vec eigval;
	mat eigvec;
	tie(eigval, eigvec) = eig_solver(A, n);

	return 1; //success
}
