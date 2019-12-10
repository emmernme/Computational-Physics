#include <iostream>
#include <armadillo>
#include <math.h>
#include "helpers.cpp"

using namespace std;
using namespace arma;


int main(){

    int n = 1.0e3;

    //Defining

    double v0x = 0;
    double v0y = 2*3.14;
    double r0x = 1.0;
    double r0y = 0;
    double m = 6*pow(10,24);
    mat a(n,2, fill::zeros);
    mat v(n,2, fill::zeros);
    mat r(n,2, fill::zeros);

    //Initial values
    v(0,0) = v0x;
    v(0,1) = v0y;
    r(0,0) = r0x;
    r(0,1) = r0y;

    euler(a, v, r, n);
    verlet(a, v, r, n);


    return 0;
}
