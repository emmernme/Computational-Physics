#ifndef JACOBI_H
#define JACOBI_H

#include <armadillo>
#include <iostream>
#include <cmath>
#include "jacobi_rotate.cpp"
#include "armadillo_eig_solver.cpp"
#include "max_offdiag.cpp"
#include "eig_solver.cpp"

using namespace std;
using namespace arma;

tuple<vec, mat> eigsolver(mat A, int n);
mat jacobi_rotate(mat A, int k, int l, int n, mat &eigvec);
double max_offdiag(mat A, int &k, int &l, int n);

#endif
