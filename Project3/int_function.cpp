#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

double int_function(double x1, double x2, double y1, double y2, double z1, double z2)
{
  int alpha = 2;
  double r1 = sqrt(x1*x1 + y1*y1 + z1*z1);
  double r2 = sqrt(x2*x2 + y2*y2 + z2*z2);
  double deno = sqrt(pow((x1-x2), 2) + pow((y1-y2), 2) + pow((z1-z2), 2));
  double value = exp(-2*alpha*(r1 + r2)) / deno ;

/*  //Writing values to file for plotting
  ofstream output;
  output.open("plotting.dat");


  output << x2 << endl;
  output << y1 << endl;
  output << y2 << endl;
  output << z1 << endl;
  output << z2 << endl;
  output << value << endl;

  output.close();
*/

  if (abs(deno) < 1E-8){
    return 0;
  }
  else {
    return value, r1, r2;
  }
}
