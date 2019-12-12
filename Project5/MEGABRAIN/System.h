#include <vector>
#include <fstream>
#include "Planet.h"
using namespace std;

#pragma once
class System {
	public: 
		// Associate with the planet class
		friend class Planet;

		// Properties of the solver
		double radius;
		double system_mass;
		double system_kinetic;
		double system_potential;
		double G;
		int planet_count;
		vector<Planet> planets;

		// Initialising methods, to create a system
		System(double radius);

		// Main functions
		void add_planet(Planet planet);
		void VelocityVerlet(int dim, int N, double end_year);
		void GravitationalForce(int dim, Planet &p1, Planet &p2, double * &F);
		void NormaliseSpeeds();

		// Helper functions
		void calc_G();
		void output(ofstream &out, int dim);
		double ** setup_matrix(int cols, int rows);
		void delete_matrix(double ** matrix, int cols, int rows);
};