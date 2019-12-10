#include <iostream>
#include "planet.cpp"
#include <string>
using namespace std;
using namespace arma;

class Planet{
    string name;
    double mass;
    mat velocity;
    mat acceleration;
    mat radi;

public:
    Planet(string x, double m, double r, double v, int n){
        string name = x;
        double mass = m;

        mat acceleration(n,n, fill::zeros);
        mat velocity(n,n, fill::zeros);
        mat radi(n,n, fill::zeros);

        v = velocity(0,0);
        r = radi(0,0);
    }

    void euler(int i, double dt, double a, double v, double r);

    vector<double> getInfo(int i){
        vector<double> info;
        info.push_back(acceleration(i));
        info.push_back(velocity(i));
        info.push_back(radi(i));
        return info;
    }
};
