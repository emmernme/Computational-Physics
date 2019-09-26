
#define CATCH_CONFIG_MAIN

#include "functions.h"
#include "catch.hpp"


TEST_CASE("Testing maxvalue"){
  int n = 3;

  mat A(n,n, fill::zeros);
  A(0, 0) = A(n-1,n-1) = 2.0;
	A(0, 1) = A(n-1,n-2) = -1.0;
	for (int i = 1; i < n-1; i++){
		A(i, i-1) = A(i, i+1) = -1.0;
		A(i, i) = 2.0;
	}
  double maxarg = 0;

  int k;
  int l;

  eig_solver(A, n, k, l);

  REQUIRE(k == 1);
  REQUIRE(l == 2);
  REQUIRE(A(k,l) == Approx(-1.0));
}

TEST_CASE("Testing eigenvalues"){
  int n = 3;
  mat A(n,n);
	A(0, 0) = A(n-1,n-1) = 2.0;
	A(0, 1) = A(n-1,n-2) = -1.0;
	for (int i = 1; i < n-1; i++){
		A(i, i-1) = A(i, i+1) = -1.0;
		A(i, i) = 2.0;
	}

  vec eigval;
  mat eigvec;

  int k;
  int l;

  tie(eigval, eigvec) = eig_solver(A, n, k, l);

  REQUIRE(eigval(0) == Approx(3.4142).epsilon(0.0001));
  REQUIRE(eigval(1) == Approx(0.5857).epsilon(0.0001));
  REQUIRE(eigval(2) == Approx(2.0000).epsilon(0.0001));
}
