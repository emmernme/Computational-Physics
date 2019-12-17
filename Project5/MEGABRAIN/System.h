/*
*	Header file for any solar system
*	Has some important constants, properties and functions
*/
#include <vector>
#include <fstream>
#include "Planet.h"
using namespace std;

#pragma once
const double _YEAR = 365.25; // Days per year
const double C = 173 * _YEAR; // Light speed in astronomical units
const double C2 = C*C; // Light speed squared

#pragma once
class System {
	public: 
		// Associate with the planet class
		friend class Planet;

		// Properties of the solver
		double radius; // For future use
		double system_mass;
		double system_kinetic;
		double system_potential;
		double G;
		double beta;
		int planet_count;
		int print_planet_count;
		vector<Planet> planets;
		bool relativistic;

		// Initialising methods, to create a system
		System(double radius, double beta = 2.0, bool relativistic = false);

		// Main functions
		void add_planet(Planet planet);
		void add_planets(vector<Planet> &planets);
		void VelocityVerlet(int dim, int N, double end_year, string filename, string title="");
		void VelocityVerletPerihelion(int dim, int N, double end_year);
		void GravitationalForce(int dim, Planet &p1, Planet &p2, double * &F);
		void NormaliseSpeeds();

		// Helper functions
		void prepare_output(ofstream &out, int dim, int N, double end_year, double dt, string title);
		void output(ofstream &out, int dim);
		double ** setup_matrix(int cols, int rows);
		void delete_matrix(double ** matrix, int cols, int rows);
		void self_destruct();
};