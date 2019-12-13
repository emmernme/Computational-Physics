#include <cmath>
#include <vector>
#include <string>

using namespace std;

#pragma once
class Planet {
	public:
		double dim; // 2D or 3D?

		// Planet properties
		string name;
		double mass;
		double *position;
		double *velocity;
		double E_potential;
		double E_kinetic;
		bool print;

		// Methods to initialize Planet
		Planet(string name, int dim, double mass, double x, double y, double z, double vx, double vy, double vz, bool print = true);

		// Various Planet-functions
		double planetary_distance(Planet secondPlanet);
		double gravitational_force(Planet secondPlanet, double G_const);
		double acceleration(Planet secondPlanet, double G_const);
		double kinetic_energy();
		double potential_energy(Planet secondPlanet, double G_const);

		// Helpers
		void print_position();
		void print_velocity();
};