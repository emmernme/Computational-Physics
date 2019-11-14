

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
#include "Ising.cpp"
#include <tuple>

using namespace std;
using namespace arma;

int main(){
  //setting up initial values and linear spacing of T
  double T0 = 1;
  double Tmax = 2.3;
  int n = 10;
  double dT = (Tmax-T0)/(double) n;
  double J = 1; // Energy scale ?
  double k_b = 1; // Boltzmann scale ?
  int N = 5e7;


  double *T = new double[n];
  //int L[4] = {40, 60, 80, 100};
  int L = 20;
  /*
  mat E_mean       (4, n-1, fill::zeros);
  mat E_sqrd_mean  (4, n-1, fill::zeros);
  mat M_mean       (4, n-1, fill::zeros);
  mat M_sqrd_mean  (4, n-1, fill::zeros);
  mat M_abs_sum    (4, n-1, fill::zeros);
  mat E_variance   (4, n-1, fill::zeros);
  mat M_variance   (4, n-1, fill::zeros);
  mat specific_heat(4, n-1, fill::zeros);
  mat suceptibility(4, n-1, fill::zeros);
  */

  for(int i = 0; i < n; i++){
    T[i] = T0+i*dT;
  }
  /*
  for(int i = 0; i < 4; i++){
    for(int k = 0; k < n-1; k++){
      E_mean       (i,k) = get<0>(MonteCarloIsing(N, true, T[k], L[i]));
      E_sqrd_mean  (i,k) = get<1>(MonteCarloIsing(N, true, T[k], L[i]));
      M_mean       (i,k) = get<2>(MonteCarloIsing(N, true, T[k], L[i]));
      M_sqrd_mean  (i,k) = get<3>(MonteCarloIsing(N, true, T[k], L[i]));
      M_abs_sum    (i,k) = get<4>(MonteCarloIsing(N, true, T[k], L[i]));
      E_variance   (i,k) = get<5>(MonteCarloIsing(N, true, T[k], L[i]));
      M_variance   (i,k) = get<6>(MonteCarloIsing(N, true, T[k], L[i]));
      specific_heat(i,k) = get<7>(MonteCarloIsing(N, true, T[k], L[i]));
      suceptibility(i,k) = get<8>(MonteCarloIsing(N, true, T[k], L[i]));
    }
  }
  */
  double *E_mean       = new double [8];
  double *E_sqrd_mean  = new double [8];
  double *M_mean       = new double [8];
  double *M_sqrd_mean  = new double [8];
  double *M_abs_sum    = new double [8];
  double *E_variance   = new double [8];
  double *M_variance   = new double [8];
  double *specific_heat= new double [8];
  double *suceptibility= new double [8];

  MonteCarloIsing(N, true, T[0], L);
  /*cout << "E_mean: " << E_mean[i] << endl;
  cout << "M_mean: " << M_mean[i] << endl;
  cout << endl;*/




  /*
  cout << setw(20) << "E_mean" << setw(15) << "     E_sqrd_mean" << setw(15);
  cout << "M_mean" << setw(15) << "M_sqrd_mean" << setw(15) << "M_abs_sum";
  cout << setw(15) << "E_variance" << setw(15) << "M_variance" << setw(15);
  cout << "specific_heat" << setw(15) << "suceptibility" << endl;
  for(int i = 0; i < 4; i++){
    for(int k = 0; k < n-1; k++){
      cout << "T: " <<  T[i] << setprecision(4) << setw(15) << E_mean(i,k) << setw(15);
      cout << setprecision(4) << E_sqrd_mean(i,k) << setw(15);
      cout << setprecision(4) << M_mean(i,k) << setw(15) << M_sqrd_mean(i,k) << setw(15);
      cout << setprecision(4) << M_abs_sum(i,k) << setw(15);
      cout << setprecision(4) << E_variance(i,k) << setw(15);
      cout << setprecision(4) << M_variance(i,k) << setw(15);
      cout << setprecision(4) << specific_heat(i,k);
      cout << setw(15) << setprecision(4) << suceptibility(i,k) << endl;
    }
  }
  */

return 0;
}
