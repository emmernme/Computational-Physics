/*
*	The Planet class provides a wrapper for a planet in a System, with its properties and methods for calculating stuff
*
*/
#include "Planet.h"

// Set up a new planet with initial properties
Planet::Planet(string name, int dim, double mass, double x, double y, double z, double vx, double vy, double vz, bool print){
	double *p = new double[3];
	p[0] = x; p[1] = y; p[2] = z;
	double *v = new double[3];
	v[0] = vx * 365; v[1] = vy * 365; v[2] = vz * 365;
	
	this->name = name;
	this->dim = dim;
	this->mass = mass;
	this->position = p;
	this->velocity = v;
	this->print = print; // Whether or not to save the positions of this planet to file
	
	E_potential = 0.0;
	E_kinetic = 0.0;
}

// Get the planetary distance from this planet to another
double Planet::planetary_distance(Planet planet){
	double r = 0.0;
	for (int i = 0; i < dim; i++) r += pow(this->position[i] - planet.position[i], 2);
	return sqrt(r);
}

// Get the gravitational force acting on this planet from another planet (unused)
double Planet::gravitational_force(Planet planet, double G_const){
	double r = this->planetary_distance(planet);
	if (r != 0) return G_const * this->mass * planet.mass / (r*r);
	return 0;
}

// Get the acceleration of the planet from the force of another planet (unused)
double Planet::acceleration(Planet planet, double G_const){
	double r = this->planetary_distance(planet);
	if (r != 0) return this->gravitational_force(planet, G_const) / (this->mass * r);
	return 0;
}

// Get the kinetic energy of the planet (unused)
double Planet::kinetic_energy(){
	double v_sum = 0.0;
	for (int i = 0; i < dim; i++) v_sum += velocity[i]*velocity[i];
	return 0.5 * mass * v_sum;
}

// Get the potential energy of the planet
double Planet::potential_energy(Planet planet, double G_const){
	return -G_const * this->mass * planet.mass / this->planetary_distance(planet);
}

// Print the position of the planet
void Planet::print_position(){
	for (int i = 0; i < dim; i++){
		cout << position[i] << ",";
	} cout << endl;
}

// Print the velocity of the planet
void Planet::print_velocity(){
	for (int i = 0; i < dim; i++){
		cout << velocity[i] << ",";
	} cout << endl;
}

// Clean up planet memory usage
void Planet::self_destruct(){
	delete [] position;
	delete [] velocity;
}