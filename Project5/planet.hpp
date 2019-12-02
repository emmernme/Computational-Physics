#include <iostream>
#include "planet.cpp"

class Planet{
    string name;
    double mass;
    mat velocity;
    mat acceleration;
    mat radi;

public:
    void initialize(std::string name,double m, double r, double v);
    double euler(int interations);

};
