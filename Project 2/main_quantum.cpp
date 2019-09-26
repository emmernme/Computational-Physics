
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

int n = 1200;

double pmax = 50;
double p0 = 0;
double h = (pmax-p0)/double(n+1);
double e = -1.0/(h*h);


double di(int i){

  double Vi = pow(p0 + h*(i+1),2);

  double d = 2.0/(h*h)+Vi;

  return d;
}

// Main function
int main(){
	// Dimensionality of the matrix
	int k;
	int l;

	// Set up the matrix as a tridiagonal matrix
	mat A(n,n, fill::zeros);
	A(0, 0) = di(0);
	A(0, 1) = A(n-1,n-2) = e;
		for (int i = 1; i < n-1; i++){
			A(i, i-1) = A(i, i+1) = e;
			A(i, i) = di(i);
	}
	// Find the eigenvalues with armadillo function
	vec arma_eigval;
	mat arma_eigvec;

  cout << "n: " << n << "   Pmax" << pmax << endl;
	// Find the eigenvalues with our own solver
	vec eigval;
	mat eigvec;



	clock_t start,finish;

	// Set up the matrix as a tridiagonal matrix

	//start timing for armadillo solver
	start = clock();
	tie(arma_eigval, arma_eigvec) = armadillo_eig_solver(A); // std::tie unwraps a tuple
	finish = clock();

	double t2 = (double (finish - start))/CLOCKS_PER_SEC;
/*
	//Start clock for jacobi method
	start = clock();

	tie(eigval, eigvec) = eig_solver(A, n, k, l);

	finish = clock();
	double t1 = (double (finish- start)) /CLOCKS_PER_SEC;

	cout << "Jacobi: " << t1 << "seconds" << endl;

	cout << "Arma: " << t2 << "seconds" << endl;

  for(int i = 0; i < 10; i++){
    cout << eigval(i) << endl;
  }
*/
  for(int i = 0; i < 10; i++){
    cout << arma_eigval(i) << endl;
  }


	return 1; //success
}
