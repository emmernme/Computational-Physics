#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "gauss_legendre.cpp"
#include "int_function.cpp"

using namespace std;


double int_function(double x);
void gauss_laguerre(double *, double *, int, double);
void gauss_legendre (double, double, double *, double *, int);

int main()
{
  int N = 100; //number of integration points
    double a = -0.45;
    double b = 0.45; //intergration limits
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
  /*
  double x2 = new double[n];
  double y1 = new double[n];
  double y2 = new double[n];
  double z1 = new double[n];
  double z2 = new double[n];
  */
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
  int_gauss += w[i]*w[j]*w[k]*w[l]*w[m]*w[n]
  *int_function(x[i], x[j], x[k], x[l], x[m], x[n]);
    }}}}}
  }

  delete [] x;
  delete [] w;
  return 0;




}
