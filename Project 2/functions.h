#ifndef JACOBI_H
#define JACOBI_H



#include "main.cpp"
#include <armadillo>
#include <iostream>
#include <cmath>

using namespace std;
using namespace arma;

int initialize();
tuple<vec, mat> eigsolver(mat A, int n);
mat jacobi_rotate(mat A, int k, int l, int n, mat &eigvec);
double max_offdiag(mat A, int &k, int &l, int n);


#endif
