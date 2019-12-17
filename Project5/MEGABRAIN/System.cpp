/*
*	The System class provides a wrapper for making an entire Solar System and calculating the positions and velocities for the system
*/
#include <iostream>
#include "System.h"
using namespace std;

// Set up a new system with intitial properties
System::System(double radius, double beta, bool relativistic, bool normaliseInitial, bool normalise) {
	this->radius = radius;
	this->system_mass = 0;
	this->system_kinetic = 0;
	this->system_potential = 0;
	this->G = 4*M_PI*M_PI;
	this->planet_count = 0;
	this->print_planet_count = 0;
	this->beta = beta;
	// Whether to include the relativistic force contribution
	this->relativistic = relativistic;
	// Whether to normalise speeds relative to the Sun's speed throughout the calculations
	this->normalise = normalise; 
	// Whether to normalise speeds relative to the Sun's speed before beginning calculations
	this->normaliseInitial = normaliseInitial; 
}

// Add a planet to the system
void System::add_planet(Planet planet){
	planets.push_back(planet);
	planet_count++;
	if (planet.print) print_planet_count++;
	system_mass += planet.mass;
}
void System::add_planets(vector<Planet> &planets){
	for (Planet planet : planets){
		add_planet(planet);
	}
}

void System::VelocityVerlet(int dim, int N, double end_year, string file, string title){
	// Calculate the time step
    double dt = end_year / (double) N;

	// Set up position and velocity matrices
	double ** acc = setup_matrix(dim, planet_count);
	double ** acc_next = setup_matrix(dim, planet_count);

	double * F = new double[dim];
	double * F_next = new double[dim];

	cout << "Starting VV. Planets: " << planet_count << ", G: " << G << ", beta: " << beta << endl;

	// Normalise the speeds of all the planets according to the sun, so that the sun's speed is 0
	if (normaliseInitial) NormaliseSpeeds();

	// Prepare the out-file
	ofstream out;
	out.open(file);
	prepare_output(out, dim, N, end_year, dt, title);

	// Precalculating - saving some flops
	double half_dt = 0.5*dt;
	double half_dt_sqrd = 0.5*dt*dt;

	// Loop over the time steps
    for (int i = 0; i < N-1; i++){

    	// Perform Velocity Verlet for each planet
		for (int p = 0; p < planet_count; p++){
			Planet &planet = planets[p];
			double inv_m = 1/planet.mass; // Precalculate

			// Reset forces
			for (int d = 0; d < dim; d++) F[d] = F_next[d] = 0.0;

			// Calculate the force contribution from all other planets
			for (int p2 = 0; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F);
			}

			// Calculate the acceleration for each dimension for the current planet, then the new position
			for (int d = 0; d < dim; d++){
				acc[p][d] = F[d] * inv_m;
				planet.position[d] += planet.velocity[d] * dt + half_dt_sqrd*acc[p][d];
			}

			// When the new position is set, calculate the next velocity by calculating the next force contribution
			// from the other planets for our planet's new position
			for (int p2 = 0; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F_next);
			}
			// Use the new acceleration to calculate the velocity of our planet
			for (int d = 0; d < dim; d++){
				acc_next[p][d] = F_next[d] * inv_m;
				planet.velocity[d] += half_dt * (acc[p][d] + acc_next[p][d]);
			}
		}

		// Make sure we look at the system compared to one planet's position
		if (normalise) NormaliseSpeeds();

		// Write data to file
		output(out, dim);
    }
	out.close();
	delete_matrix(acc, dim, planet_count);
	delete_matrix(acc_next, dim, planet_count);
	delete [] F; delete [] F_next;
}

void System::VelocityVerletPerihelion(int dim, int N, double end_year){
	// Calculate the time step
    double dt = end_year / (double) N;

	// Set up position and velocity matrices
	double ** acc = setup_matrix(dim, planet_count);
	double ** acc_next = setup_matrix(dim, planet_count);

	double * F = new double[dim];
	double * F_next = new double[dim];

	// Normalise the speeds of all the planets according to the sun, so that the sun's speed is 0
	NormaliseSpeeds();
	
	// Precalculating
	double half_dt = 0.5*dt;
	double half_dt_sqrd = 0.5*dt*dt;

	// Loop over the time steps
    for (int i = 0; i < N-1; i++){
    	// Perform Velocity Verlet for each planet
		for (int p = 0; p < planet_count; p++){
			Planet &planet = planets[p];
			double inv_m = 1/planet.mass; // Precalculate

			// Reset forces
			for (int d = 0; d < dim; d++){
				F[d] = F_next[d] = 0.0; 
			}

			// Calculate the force contribution from all other planets
			for (int p2 = 0; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F);
			}

			// Calculate the acceleration for each dimension for the current planet, then the new position
			for (int d = 0; d < dim; d++){
				acc[p][d] = F[d] * inv_m;

				// Calculate the new position with VV
				planet.position[d] += planet.velocity[d] * dt + half_dt_sqrd*acc[p][d];
			}

			// When the new position is set, calculate the next velocity by calculating the next force contribution
			// from the other planets for our planet's new position
			for (int p2 = 0; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F_next);
			}
			// Use the new acceleration to calculate the velocity of our planet
			for (int d = 0; d < dim; d++){
				acc_next[p][d] = F_next[d] * inv_m;

				// Calculate the new velocity with VV
				planet.velocity[d] += half_dt * (acc[p][d] + acc_next[p][d]);
			}
		}
		// Make sure we look at the system compared to the sun's position
		NormaliseSpeeds(); // We actually might not need this, though...
    }
	delete_matrix(acc, dim, planet_count);
	delete_matrix(acc_next, dim, planet_count);
	delete [] F; delete [] F_next;
}

// Calculate the gravitational attraction between two planets
void System::GravitationalForce(int dim, Planet &p1, Planet &p2, double * &F){
	double r = p1.planetary_distance(p2);
	if (r < 1e-10) return;

	// Calculate the relativistic contribution (1 + 3*l*l/(r*r*c*c))
	double rel = 1.0;
	if (relativistic){
		double *p = p1.position;
		double *v = p1.velocity;
		double l2 = pow(p[1]*v[2]-p[2]*v[1], 2)
				 + pow(p[0]*v[2]-p[2]*v[0], 2)
				 + pow(p[0]*v[1]-p[1]*v[0], 2);
		rel += 3.0*l2/(r*r*C2);
	}

	// Calculate the relative distances and the force contributions in each direction
	double factors = G*p1.mass*p2.mass * rel / pow(r, beta + 1);
	for (int i = 0; i < dim; i++){
		double rel_dist = p1.position[i] - p2.position[i];
		F[i] -= rel_dist * factors;
	}
}

// Normalise planet speeds according to the first planet (the Sun)
void System::NormaliseSpeeds(){
	double *vel = planets[0].velocity;
	for (int i = 0; i < planet_count; i++){
		for (int d = 0; d < planets[i].dim; d++){
			planets[i].velocity[d] -= vel[d];
		}
	}
}

// Write the start information of the data to file
void System::prepare_output(ofstream &out, int dim, int N, double end_year, double dt, string title){
	out << "# Next line: [dim],[# integration points],[years],[dt],[system radius],[planet count],[beta],[title]" << endl;
	out << dim << "," << N << "," << end_year << "," << dt << "," << radius << "," << print_planet_count << "," << beta << "," << title << endl;
	out << "# Next lines: [planet ID],[planet name]" << endl;
	for (int i = 0; i < planet_count; i++){
		if (planets[i].print == false) continue;
		out << i << "," << planets[i].name << endl;
	}
	out << "# Next lines: [planet ID]=[x],[y]" << ((dim == 3)?",[z]":"") << endl;
	
	// Print the initial positions
	output(out, dim);
}

// Write the positions to file
void System::output(ofstream &out, int dim){
	for (int i = 0; i < planets.size(); i++){
		Planet &planet = planets[i];
		if (planet.print == false) continue;
		out << i << "=";
		for (int d = 0; d < dim; d++){
			out << planet.position[d] << ((d == dim-1)? "\n" : ",");
		}
	}
}

// Prepare a 2D matrix as an array
double ** System::setup_matrix(int cols, int rows){
	double ** matrix;
	matrix = new double *[rows];

	// Allocate memory
	for (int i = 0; i < rows; i++){
		matrix[i] = new double[cols];
		for (int j = 0; j < cols; j++){
            matrix[i][j] = 0.0;
        }
	}
	return matrix;
}

// Deallocate memory allocated for a 2D array
void System::delete_matrix(double **matrix, int cols, int rows){
    for (int i = 0; i < rows; i++)
        delete [] matrix[i];
    delete [] matrix;
}

// Deallocate memory for the system
void System::self_destruct(){
	for (int i = 0; i < planet_count; i++){
		planets[i].self_destruct();
	}
}