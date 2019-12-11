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
    double m = 6.0E24;
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

  /*
    vec E(n);
    vec E_diff(n);

    double Ekx;
    double Eky;
    double Epx;
    double Epy;
    double Ek;
    double Ep;
    double G = 1.97E-29;
    double GM = 4 * pow(M_PI,2);


    double E0 = 0.5*m*v0y*v0y + GM *m/r0x;
    cout << GM *m/r0x << endl;

    for(int i=0; i<n; i++){
        Ekx = 0.5 * m * v(i,0) * v(i,0);
        Eky = 0.5 * m * v(i,1) * v(i,1);
        Epx = -m * GM / r(i,0);
        Epy = -m * GM / r(i,1);

        Ek = sqrt(Ekx*Ekx + Eky*Eky);
        Ep = sqrt(Epx*Epx + Epy*Epy);

        E(i) = Ek + Ep;
        E_diff(i) = E0 - E(i);
    }

    ofstream outfile;
    outfile.open("energy.dat");
    outfile << E_diff;
 */

    double omega;
    double I;
    vec L(n);

    for(int i = 0; i<n; i++){
        L(i) = m*(sqrt(v(i,0)*v(i,0)+v(i,1)*v(i,1))* (r(i,0)*r(i,0)*r(i,1)-1/(r(i,1)*r(i,1))*r(i,0)));
    }

    ofstream rotate;
    rotate.open("rotate.dat");
    rotate << L;

    return 0;
}