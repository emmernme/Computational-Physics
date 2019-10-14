
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "gauss_legendre.cpp"
#include "int_function.cpp"



TEST_CASE("Testing the integration value for Gauss-Legendre"){

  int N = 27; //number of integration points
    double a = -2.89;
    double b = 2.89; //intergration limits
  /*
  cout << "Number of integration points:"<< endl;
  cin >> N;
  cout <<"Integratiom limits(-lambda, lambda)" << endl;
  cin >> a >> b;
  */
  int alpha = 2;

  //vectors containg the mesh points weights and
  //function values
  double *x = new double[N];
  double *w = new double[N];

  // set up the mesh points and weights
  gauss_legendre(a, b, x, w, N);

  //Evaluate the integral with the Gauss-Legendre method
  double int_gauss = 0.;

  for (int i=0; i < N; i++){
      for (int j = 0; j<N; j++){
      for (int k = 0; k<N; k++){
      for (int l = 0; l<N; l++){
      for (int m = 0; m<N; m++){
      for (int n = 0; n<N; n++){

  int_gauss += w[i]*w[j]*w[k]*w[l]*w[m]*w[n]*int_function(x[i], x[j], x[k], x[l], x[m], x[n]);
    }}}}}
  }

  double exact_value = 0.192765;

  REQUIRE(int_gauss == Approx(exact_value).epsilon(0.0001));

}
