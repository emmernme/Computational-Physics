#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

double int_function(double x1, double x2, double y1, double y2, double z1, double z2)
{
  int alpha;
  double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
  double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
  double deno = sqrt(pow((x1-x2), 2) + pow((y1-y2), 2) + pow((z1-z2), 2));
  double value = exp((-2*alpha*(r1 - r2)) / deno );
  return value;
}
