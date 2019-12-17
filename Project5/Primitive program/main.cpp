#include <iostream>
#include <armadillo>
#include <math.h>
#include "helpers.cpp"

using namespace std;
using namespace arma;


int main(){

    int n = 1.0e3;

    //Defining initial values and setting up matrices
    double v0x = 0;
    double v0y = 2*3.14;
    double r0x = 1.0;
    double r0y = 0;
    double m = 6.0E24;
    mat a(n,2, fill::zeros);
    mat v(n,2, fill::zeros);
    mat r(n,2, fill::zeros);

    //Inserting the initial values to the matrices
    v(0,0) = v0x;
    v(0,1) = v0y;
    r(0,0) = r0x;
    r(0,1) = r0y;

    //Following is the two methods with time taking
    clock_t start, finish;
    start = clock();
    euler(a, v, r, n);  //Calls on the Euler forward method
    finish = clock();
    double t_euler = (double) (finish-start)/CLOCKS_PER_SEC * 1000;

    start = clock();
    verlet(a, v, r, n); //Calls on the Verlet method
    finish = clock();
    double t_verlet = (double) (finish-start)/CLOCKS_PER_SEC *1000;

    cout << "Integration points: " << n << endl;
    cout << "Time taken for Euler method:  " << t_euler << "ms" << endl;
    cout << "Time taken for Verlet method: " << t_verlet << "ms" << endl;
    


    //Making vectors for storing energy values
    vec E(n);
    vec E_diff(n);

    //prepearing for energy calculation
    double Ekx;
    double Eky;
    double Epx;
    double Epy;
    double Ek;
    double Ep;
    double G = 1.97E-29;
    double GM = 4 * pow(M_PI,2);


    double E0 = 0.5*m*v0y*v0y - GM *m/r0x; //Energy for the initial values

    //Running through the velocity and position to calculate the energy
    for(int i=0; i<n; i++){
        Ekx = 0.5 * m * v(i,0) * v(i,0);
        Eky = 0.5 * m * v(i,1) * v(i,1);
        Epx = -m * GM * r(i,0);
        Epy = -m * GM * r(i,1);

        Ek = (sqrt(Ekx*Ekx + Eky*Eky));
        Ep = Epx + Epy;

        E(i) = Ek + Ep;
        E_diff(i) = E0 - E(i);
    }
    //Prepearing for calculation of the angular momentum
    double omega;
    double I;
    vec L(n);

    //Loopes over the velocity and position to calculate the angular momentum
    for(int i = 0; i<n; i++){
        L(i) = m*(sqrt(v(i,0)*v(i,0)+v(i,1)*v(i,1))* (r(i,0)*r(i,0)*r(i,1)-1/(r(i,1)*r(i,1))*r(i,0))); //Angular momentum
    }


 //Writes the values to a file for plotting in python
    cout << E;
    ofstream outfile;
    outfile.open("energy.dat");
    outfile << E_diff;
    ofstream rotate;
    rotate.open("rotate.dat");
    rotate << L;

    return 0;
}
