#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


double int_function(double x);
void gauss_laguerre(double *, double *, intn double);
double trapezodial_rule(double, double, int, double (*func)(double) );
double simpson (double, double, int, double(*func)(double) );
void gauss_legendre (double, double, double *, double *, int);
double gammln(double);

int main()
{
  int n = 100; //number of integration points
  double a = - lambda; double b = lambda; //intergration limits
  int alfa = 2;

  double x1 = new double[n];
  double x2 = new double[n];
  double y1 = new double[n];
  double y2 = new double[n];
  double z1 = new double[n];
  double z2 = new double[n];



}

double int_function(double x)
{
  double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
  double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
  double value = exp(-2*alfa*(r1 - r2)) / (abs(r1-r2) );
  return value;
}

/*
a og b er grensene på integralet men de er lambda
*/

void gauss_legendre(double a, double b, double x[], double w[], int n)
{
  int m,j,i;

  //legendre polynomene:

  double r, s, t;
  int m;
  r = 0; s = 1;

  for (m=0; m < n; m++)
  {
    t = r; r = s;
    s = (2*m+1)*x*r - m*t;
    s /= (m+1);
  }



}
