

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
#include "ising.cpp"

using namespace std;

int main(){
  double T0 = 1;
  double Tmax = 10;
  int n = 100;
  double dT = (Tmax-T0)/n;
  double J = 1; // Energy scale ?
  double k_b = 1; // Boltzmann scale ?

  double T[100] = {};

  int N = 1000; //Number of MC cycles


  for(int i = 0; i < n; i++){
    T[i] = T0+i*dT;
  }

  for(int k = 0; k < n; k++){
    double beta = 1 * T[k]; //  / (k_b * T);
    MonteCarloIsing(N, true);
  }



  return 0;
}
