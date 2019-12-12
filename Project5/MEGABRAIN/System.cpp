/*
*	The System class provides a wrapper for making an entire Solar System and calculating the positions and velocities for the system
*/
#include <iostream>
#include "System.h"
using namespace std;

System::System(double radius, double beta) {
	// Set the initial properties of the system
	this->radius = radius;
	system_mass = 0;
	system_kinetic = 0;
	system_potential = 0;
	G = 4*M_PI*M_PI;
	planet_count = 0;
	this->beta = beta;
}

void System::add_planet(Planet planet){
	planets.push_back(planet);
	planet_count++;
	system_mass += planet.mass;
}
void System::calc_G(){
	G = (4*M_PI*M_PI);
	//G = (4*M_PI*M_PI/32)*radius*radius*radius / system_mass;
}

void System::VelocityVerlet(int dim, int N, double end_year, string file){
	// Calculate the time step
    double dt = end_year / (double) N;

	// Set up position and velocity matrices
	double ** acc = setup_matrix(dim, planet_count);
	double ** acc_next = setup_matrix(dim, planet_count);

	double * F = new double[dim];
	double * F_next = new double[dim];

	// Prepare values used in calculations
	calc_G();
	NormaliseSpeeds();
	double rad_sqrd = radius*radius;

	// Prepare the out-file
	ofstream out;
	out.open(file);
	out << "# Next line: [dim],[# integration points],[years],[dt],[system radius],[planet count],[beta]" << endl;
	out << dim << "," << N << "," << end_year << "," << dt << "," << radius << "," << planet_count << "," << beta << endl;
	out << "# Next lines: [planet ID],[planet name]" << endl;
	for (int i = 0; i < planet_count; i++){
		out << i << "," << planets[i].name << endl;
	}
	out << "# Next lines: [planet ID]=[x],[y]" << ((dim == 3)?",[z]":"") << endl;
	
	// Print the initial positions
	output(out, dim);
	cout << "Starting VV. Planets: " << planet_count << ", G: " << G << ", beta: " << beta << endl; 

	// Loop over the time steps
    for (int i = 0; i < N-1; i++){
    	// Perform Velocity Verlet for each planet
		for (int p = 0; p < planet_count; p++){
			Planet &planet = planets[p];
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
				acc[p][d] = F[d] / planet.mass;

				// Calculate the new position with VV
				planet.position[d] += planet.velocity[d] * dt + 0.5*dt*dt*acc[p][d];
			}

			// When the new position is set, calculate the next velocity by calculating the next force contribution
			// from the other planets for our planet's new position
			for (int p2 = 0; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F_next);
			}
			// Use the new acceleration to calculate the velocity of our planet
			for (int d = 0; d < dim; d++){
				acc_next[p][d] = F_next[d] / planet.mass;

				// Calculate the new velocity with VV
				planet.velocity[d] += 0.5 * dt*(acc[p][d] + acc_next[p][d]);
			}
		}
		NormaliseSpeeds();
		// Write data to file
		output(out, dim);
    }
	out.close();
	delete_matrix(acc, dim, planet_count);
	delete_matrix(acc_next, dim, planet_count);
	delete [] F; delete [] F_next;
}

// Calculate the gravitational attraction between two planets
void System::GravitationalForce(int dim, Planet &p1, Planet &p2, double * &F){
	double r = p1.planetary_distance(p2);
	if (r < 1e-10) return;

	double r_factor = pow(r, beta + 1);

	// Calculate the relative distances and the force contributions in each direction
	for (int i = 0; i < dim; i++){
		double rel_dist = p1.position[i] - p2.position[i];
		F[i] -= G * p1.mass * p2.mass * rel_dist / r_factor;
	}
}

// Normalise planet speeds according to the first planet
void System::NormaliseSpeeds(){
	double *vel = planets[0].velocity;
	for (int i = 0; i < planet_count; i++){
		for (int d = 0; d < planets[i].dim; d++){
			planets[i].velocity[d] -= vel[d];
		}
	}
}

// Write the positions to file
void System::output(ofstream &out, int dim){
	for (int i = 0; i < planets.size(); i++){
		Planet &planet = planets[i];
		out << i << "=";
		for (int d = 0; d < dim; d++){
			out << planet.position[d] << ((d == dim-1)? "\n" : ",");
		}
	}
}

double ** System::setup_matrix(int cols, int rows){
	// Setting up a 2D "matrix" as an array
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
void System::delete_matrix(double **matrix, int cols, int rows){
	// Deallocate memory of a 2D array
    for (int i = 0; i < rows; i++)
        delete [] matrix[i];
    delete [] matrix;
}
