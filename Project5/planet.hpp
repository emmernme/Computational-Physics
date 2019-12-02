#include <iostream>
#include "planet.cpp"

class Planet{
    string name;
    double mass;


public:
    mat velocity;
    mat acceleration;
    mat radi;

    void initialize(std::string name,double m, double r, double v);
    void euler(int i, double dt, mat acceleration, mat velocity, mat radi);

};
