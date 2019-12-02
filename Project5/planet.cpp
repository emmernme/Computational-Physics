#include <iostream>
#include <math.h>
using namespace std;
using namespace arma;

void initialize(string new_name, double m, mat v, mat r){
    string name = new_name;
    double mass = m;
    mat velocity = v;
    mat radi = r;
}


void euler(int i, mat acceleration, mat velocity, mat radi){
    double GM = 4 * pow(M_PI,2);

    acceleration(i,0) = (GM)/pow(radi(i,0),2);
    acceleration(i,1) = (GM)/pow(radi(i,1),2);


    velocity(i+1,0)= velocity(i,0) + acceleration(i,0)*dt;
    velocity(i+1,1)= velocity(i,1) + acceleration(i,1)*dt;

    radi(i+1,0) = radi(i,0) + velocity(i,0)*dt;
    radi(i+1,1) = radi(i,1) + velocity(i,1)*dt;

}
