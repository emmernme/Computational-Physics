#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

// For solving with Jacobi's method
mat jacobi_rotate(mat A, int k, int l, int n, mat &eigvec){
	double s, c; // sin, cos

	// Skip some calculations if a_kl = 0
	if (A(k,l) == 0){
		s = 0.0;
		c = 1.0;
	} else {
		double t, tau;
		tau = (A(l,l) - A(k,k))/(2*A(k,l));
		// Not sure what this does
		if (tau >= 0){
			t = 1.0/(tau + sqrt(1.0 + tau*tau));
		} else {
			t = -1.0 /(-tau + sqrt(1.0 + tau*tau));
		}

		// Calculate cos, sin
		c = 1.0/sqrt(1.0 + t*t);
		s = t * c;
	}


	// Set up the new matrix and the max values (of the old matrix)
	mat B = A;
	B(0,0) = A(0,0);
	B(k, k) = A(k,k)*pow(c,2) - 2.0*A(k,l)*c*s + A(l,l)*pow(s,2);
	B(l, l) = A(l,l)*pow(c,2) + 2.0*A(k,l)*c*s + A(k,k)*pow(s,2);
	B(k, l) = B(l, k) = 0.0;

	// Set the non-diagonal elements for each row
	for (int i = 0; i < n; i++){
		if (i != k && i != l){
			B(i,i) = A(i,i);
			B(i, k) = A(i,k)*c - A(i,l)*s;
			B(i, l) = A(i,l)*c + A(i,k)*s;
			B(k, i) = B(i,k);
			B(l, i) = B(i,l);
		}

   		// Saving eigvec(i,k) before defining a new one
    	mat e = eigvec;
    	e(i,k) = eigvec(i,k);

		// Set the new eigenvectors
    	eigvec(i,k) = c * eigvec(i,k) - s * eigvec(i,l);
		eigvec(i,l) = c * eigvec(i,l) + s * e(i,k);
	}
	return B;
}
