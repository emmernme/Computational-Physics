/*
*	The Planet class provides a wrapper for a planet in a System, with its properties and methods for calculating stuff
*
*/
#include "Planet.h"

Planet::Planet(int dim, double mass, double* p, double* v){
	this->dim = dim;
	this->mass = mass;
	this->position = p;
	this->velocity = v;
	
	E_potential = 0.0;
	E_kinetic = 0.0;
}
Planet::Planet(double mass, double x, double y, double z, double vx, double vy, double vz){
	double *p = new double(3);
	p[0] = x, p[1] = y, p[2] = z;
	double *v = new double(3);
	v[0] = vx, v[1] = vy, v[2] = vz;
	
	this->dim = 3;
	this->mass = mass;
	this->position = p;
	this->velocity = v;
	
	E_potential = 0.0;
	E_kinetic = 0.0;
}
Planet::Planet(double mass, double x, double y, double vx, double vy){
	double *p = new double(2);
	p[0] = x, p[1] = y;
	double *v = new double(2);
	v[0] = vx, v[1] = vy;
	
	this->dim = 2;
	this->mass = mass;
	this->position = p;
	this->velocity = v;
	
	E_potential = 0.0;
	E_kinetic = 0.0;
}

double Planet::planetary_distance(Planet planet){
	double a = 0.0;
	for (int i = 0; i < dim; i++){
		a += pow(this->position[i] - planet.position[i], 2);
	}
	return sqrt(a);
}

double Planet::gravitational_force(Planet planet, double G_const){
	double r = this->planetary_distance(planet);
	if (r != 0) return G_const * this->mass * planet.mass / (r*r);
	return 0;
}
double Planet::acceleration(Planet planet, double G_const){
	double r = this->planetary_distance(planet);
	if (r != 0) return this->gravitational_force(planet, G_const) / (this->mass * r);
	return 0;
}
double Planet::kinetic_energy(){
	double v_sum = 0.0;
	for (int i = 0; i < dim; i++){
		v_sum += velocity[i]*velocity[i];
	}
	return 0.5 * mass * v_sum;
}
double Planet::potential_energy(Planet planet, double G_const){
	return -G_const * this->mass * planet.mass / this->planetary_distance(planet);
}