#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

//legendre polynomene:
double legendre(int n, double x)
{
  double r, s, t;
  int m;
  r = 0; s = 1;

  for (m=0; m < N; m++)
  {
    t = r; r = s;
    s = double((2*m+1)*x*r) - double(m*t);
    s /= (m+1);
  }
}
