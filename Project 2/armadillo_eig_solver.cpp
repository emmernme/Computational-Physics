#include <iostream>
#include <tuple>
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
