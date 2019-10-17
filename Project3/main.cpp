#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "gauss_legendre.cpp"
#include "int_function.cpp"
#include "gauss_laguerre.cpp"
#include "int_function_polar.cpp"

#define ZERO 1.0e-10

using namespace std;


int main()
{
  int N = 10; //number of integration points
  double a = 3;
  double b = 3; //intergration limits

  clock_t start, finish;

  int alpha = 2;
  double      const  pi = 3.14159265359;

  //vectors containg the mesh points, weights and function values
  double *x = new double[N];
  double *w = new double[N];

  // arrays for gauss_laguerre
  double *r = new double [N+1]; //mesh points 0 to inf laguerre
  double *w_r = new double [N+1]; //corresponding weights
  double *theta = new double[N]; //mesh point for theta, 0 to pi from legendre
  double *w_t = new double[N]; //corresponding weights
  double *phi = new double[N]; //mesh points for phi 0 to 2pi from legendre
  double *w_p = new double [N]; //corresponding weights

  // gauss_laguerre; set up the mesh points and weights and the power of x^alf
  double alf = 0;
  gauss_laguerre(r, w_r, N, alf);

  // Gauss Legendre; set up the mesh points and weights
  gauss_legendre(a, b, x, w, N);


  gauss_legendre(0, pi, theta, w_t, N);
  gauss_legendre(0, 2*pi, phi, w_p, N);

  //Evaluate the integral with the Gauss-Legendre method
  double int_gauss = 0.;

  start = clock();

  for (int i=0; i < N; i++){
      for (int j = 0; j<N; j++){
      for (int k = 0; k<N; k++){
      for (int l = 0; l<N; l++){
      for (int m = 0; m<N; m++){
      for (int n = 0; n<N; n++){


  int_gauss += w[i]*w[j]*w[k]*w[l]*w[m]*w[n]*int_function(x[i], x[j], x[k], x[l], x[m], x[n]);
    }}}}}
  }

  finish = clock();
  double t1 = (double (finish - start))/CLOCKS_PER_SEC;

  //evaluate the intergrak with the Gauss-Laguerre method
  // we initialize the sum
  double int_gausslag = 0.;

  start = clock();

  for (int i=1; i < N; i++){
        for (int j = 1; j<N; j++){
        for (int k = 0; k<N; k++){
        for (int l = 0; l<N; l++){
        for (int m = 0; m<N; m++){
        for (int n = 0; n<N; n++){
    int_gausslag += w_r[i]*w_r[j]*w_t[k]*w_t[l]*w_p[m]*w_p[n]*int_function_polar(r[i], r[j], theta[k], theta[l], phi[m], phi[n]);
    }}}}}
}

  finish = clock();
  double t2 = (double (finish - start))/CLOCKS_PER_SEC;

  double exact = 0.192765;
  double diff1 = fabs(int_gauss - exact);
  double diff2 = fabs(int_gausslag - exact);


  cout << "Exact value:" << setw(26) << exact << endl;
  cout << "Gaussian Legendre quadrature: " << setw(6) << fixed << setprecision(6);
  cout << int_gauss << "   Diff: " << diff1 << "   Time taken: "<< t1 << endl;
  cout << "Gaussian Laguerre quadrature: " << setw(6) << fixed << setprecision(6);
  cout << int_gausslag << "   Diff: " << diff2 << "   Time taken: " << t2 << endl;

  delete [] x;
  delete [] w;
  delete [] w_r;
  delete [] r;
  delete [] theta;
  delete [] phi;
  delete [] w_t;
  delete [] w_p;

  return 0;

}
