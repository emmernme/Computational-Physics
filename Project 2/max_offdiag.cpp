
#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;



// Finds the maximum value and its index in the matrix
double max_offdiag(mat A, int &k, int &l, int n){
	double maxarg = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (i != j && (fabs(maxarg) < fabs(A(i,j)))){
				maxarg = fabs(A(i,j));
				k = i;
				l = j;
			}
		}
	}
	return maxarg;
}
