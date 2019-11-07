

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
#include "Ising.cpp"

using namespace std;

int main(){
  //setting up initial values and linear spacing of T
  double T0 = 2;
  double Tmax = 2.3;
  int n = 10;
  double dT = (Tmax-T0)/(double) n;
  double J = 1; // Energy scale ?
  double k_b = 1; // Boltzmann scale ?
  int N = 100000;

  double *T = new double[n];
  //int L = 2;
  int L[4] = {40, 60, 80, 100};

  for(int i = 0; i < n; i++){
    T[i] = T0+i*dT;
  }

  for(int i = 0; i < 4; i++){
    for(int k = 0; k < n; k++){
      double E_mean = MonteCarloIsing(N, true, T[k], L[i]);
      cout << setprecision(8) << E_mean << endl;
    }
    cout << endl;
  }



  return 0;
}
