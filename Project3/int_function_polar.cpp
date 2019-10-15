#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#define ZERO 1.0e-10

using namespace std;

double int_function_polar(double x1, double x2, double y1, double y2, double z1, double z2, double theta_1, double theta_2, double phi_1, double phi_2)
{
  double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
  double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
  double deno = r1*r1+r2*r2-2*r1*r2*cosb;
  double cosb = cos(theta_1)*cos(theta_2) + sin(theta_1)*sin(theta_2)*cos(phi_1-phi_2);
  double f = exp(-3*(r1+r2))*r1*r1*r2*r2*sin(theta_1)*sin(theta_2)/sqrt(deno);
    if(deno > ZERO)
          return f;
    else
          return 0;

}
