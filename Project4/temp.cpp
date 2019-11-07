

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>


using namespace std;

int main(){
  double T0 = 1;
  double Tmax = 10;
  int n = 100;
  double dT = (Tmax-T0)/n;

  double T[100] = {};

  for(int i = 0; i < n; i++){
    T[i] = T0+i*dT;
  }

  for(int k = 0; k < n; k++){
    //Loop ising.cpp her
  }



  return 0;
}
