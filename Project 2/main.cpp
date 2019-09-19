
//This file uses armadillo, compile using "<compiler> <filename> -larmadillo"

#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;


// test function for armadillo diagonalization tool.
int test(mat A){


  vec eigval;
  mat eigvec;

  eig_sym(eigval, eigvec, A);

  cout << A << endl;
  cout << eigval << endl;
  cout << eigvec << endl;

  return 1;
}

//function for solving with jacobi's method

mat jacobi_rotate(mat A, int k, int l, int  n){

double s, c;


  if (A(k,l) == 0){
    s = 0.0;
    c = 1.0;
  }
  else {
    double t, tau;
    tau = (A(l,l) - A(k,k))/2*A(k,l);
    if (tau >= 0){
      t = - tau + sqrt(1.0+ tau*tau);
    }
    else {
    t = - tau - sqrt(1.0+ tau*tau);
    }
    c = 1.0/sqrt(1.0 + t*t);
    s = t * c;
  }
  cout << k << "   " << l << endl;
  mat B(3,3);
  B(0,0) = A(0,0);
  B(k, k) = A(k,k)*pow(c,2)-2.0*A(k,l)*c*s + A(l,l)*pow(s,2);
  B(l, l) = A(l,l)*pow(c,2)+2.0*A(k,l)*c*s + A(k,k)*pow(s,2);
  B(k, l) = 0.0;
  B(l, k) = 0.0;

  for (int i = 0; i < 3; i++){
    if (i != k && i!= l){
      B(i, k) = A(i,k)*c - A(i,l)*s;
      B(i, l) = A(i,l)*c + A(i,k)*s;
      B(k, i) = B(i,k);
      B(l, i) = B(i,l);
    }
  }

  cout << B << endl;
  return B;
}


//Finds maximum value and index for the matrix
double max_offdiag(mat A, int &k, int &l, int n){

  double maxarg = 0;

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (i != j && fabs( maxarg )< fabs( A(i,j))){
        maxarg = fabs (A(i,j));
        k = i;
        l = j;
      }
    }
  }
  return maxarg;
}


int jacobi(mat A, int n){
  //Setting initial values and tolleration value
  int k= 0; int l = 0;
  double tol = 10e-8;
  double max_iterations = pow(n, 3);
  double iterations = 0;
  double max = max_offdiag(A, k, l, n);


  while (iterations < max_iterations && max > tol){
    A = jacobi_rotate(A, k, l, n);
    max = max_offdiag(A, k, l, n);

    iterations++;
  }
  cout << max << endl;
  cout << iterations << endl;
  return 1;
}


int main() {
  int n = 10;


  mat A(3,3);

  A(0, 0) = A(3-1,3-1) = 2;
	A(0, 1) = A(3-1,3-2) = -1;
	for (int i = 1; i < 3-1; i++){
		A(i, i-1) = A(i, i+1) = -1;
		A(i, i) = 2;
	}

  //Calling test function
  //test(A);

  //Running the jacobi method
  jacobi(A, n);
  //cout << B;

  return 1; //success
}
