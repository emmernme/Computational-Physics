#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "gauss_legendre.cpp"
#include "int_function.cpp"
#include "gauss_laguerre.cpp"
#include "int_function_polar.cpp"

using namespace std;

double int_function(double x1, double x2, double y1, double y2, double z1, double z2);
double int_function_polar(double x1, double x2, double y1, double y2, double z1, double z2, double theta_1, double theta_2, double phi_1, double phi_2);
void gauss_legendre(double a, double b, double x[], double w[], int N);
void gauss_laguerre(double *x, double *w, int N, double alf);

int main()
{
  int N = 27; //number of integration points
  double a = -2.89;
  double b = 2.89; //intergration limits

  int alpha = 2;
  double      const  pi = 3.14159265359;

  //vectors containg the mesh points weights and
  //function values
  double *x = new double[N];
  double *w = new double[N];

  // arrays for gauss_laguerre
  double *xgl = new double [N+1];
  double *theta = new double[N+1];
  double *phi = new double[N+1];
  double *wgl = new double [N+1];

  // Gauss Legendre; set up the mesh points and weights
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
  // gauss_laguerre; set up the mesh points and weights and the power of x^alf
  double alf = 1.0;
  gauss_laguerre(xgl, wgl, N, alf);

  //evaluate the intergrak with the Gauss-Laguerre method
  // we initialize the sum
  double int_gausslag = 0.;
  for (int i=0; i < N; i++){
        for (int j = 0; j<N; j++){
        for (int k = 0; k<N; k++){
        for (int l = 0; l<N; l++){
        for (int m = 0; m<N; m++){
        for (int n = 0; n<N; n++){
        for (int o = 0; o<pi/N; o++){
        for (int p = 0; p<pi/N; p++){
        for (int r = 0; r<2*pi/N; r++){
        for (int q = 0; q<2*pi/N; q++){

    int_gausslag += wgl[i]*wgl[j]*wgl[k]*wgl[l]*wgl[m]*wgl[n]*int_function_polar(xgl[i], xgl[j], xgl[k], xgl[l], xgl[m], xgl[n], theta[o], theta[p], phi[r], phi[q]);
    }}}}}}}}}
    }

  cout << "Exact value = 0.192765" << endl;
  cout << "Gaussian Legendre quadrature = " << setw(20) << setprecision(15) << int_gauss << endl;
  cout << "Gaussian Laguerre quadrature = " << setw(20) << setprecision(15) << int_gausslag << endl;

  delete [] x;
  delete [] w;
  delete [] wgl;
  delete [] xgl;
  delete [] theta;
  delete [] phi;
  return 0;

}
