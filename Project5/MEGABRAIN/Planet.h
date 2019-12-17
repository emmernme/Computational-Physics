#include <cmath>
#include <vector>
#include <string>

using namespace std;

#pragma once
class Planet {
	public:
		// Planet properties
		double dim; // 2D or 3D?
		string name;
		double mass;
		double *position;
		double *velocity;
		double E_potential;
		double E_kinetic;
		bool print;

		// Methods to initialize Planet
		Planet(string name, int dim, double mass, double x, double y, double z, double vx_per_day, double vy_per_day, double vz_per_day, bool print = true);

		// Various Planet-functions
		double planetary_distance(Planet secondPlanet);
		double gravitational_force(Planet secondPlanet, double G_const);
		double acceleration(Planet secondPlanet, double G_const);
		double kinetic_energy();
		double potential_energy(Planet secondPlanet, double G_const);

		// Helpers
		void print_position();
		void print_velocity();
		void self_destruct();
};