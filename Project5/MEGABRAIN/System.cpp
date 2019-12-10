/*
*	The System class provides a wrapper for making an entire Solar System and calculating the positions and velocities for the system
*	Compile using
	g++ simulator.cpp Planet.cpp System.cpp -o simulator.o -O3 -std=c++11
*/
#include "System.h"

System::System(double radius) {
	// Set the initial properties of the system
	this->radius = radius;
	system_mass = 0;
	system_kinetic = 0;
	system_potential = 0;
	G = 4*M_PI*M_PI;
	planet_count = 0;
}

void System::add_planet(Planet planet){
	planets.push_back(planet);
	planet_count++;
	system_mass += planet.mass;
}
void System::calc_G(){
	G = (4*M_PI*M_PI/32)*radius*radius*radius / system_mass;
}

void System::VelocityVerlet(int dim, int N, double end_year){
	// Calculate the time step
    double dt = end_year / (double) N;

	// Set up position and velocity matrices
	double ** acc = setup_matrix(planet_count, dim);
	double ** acc_next = setup_matrix(planet_count, dim);

	double * F = new double(dim);
	double * F_next = new double(dim);

	// Prepare values used in calculations
	calc_G();
	double rad_sqrd = radius*radius;

	// Loop over the time steps
    for (int i = 0; i < N-1; i++){

    	// Perform Velocity Verlet for each planet
		for (int p = 0; p < planet_count; p++){
			Planet &planet = planets[p];
			F[0]=F[1]=F[2]=F_next[0]=F_next[1]=F_next[2] = 0.0; // Reset forces

			// Calculate the force contribution from all other planets
			for (int p2 = p+1; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F);
			}

			// Calculate the acceleration for each dimension for the current planet, then the new position
			for (int d = 0; i < dim; d++){
				acc[p][d] = F[d] * planet.mass;

				// Calculate the new position with VV
				planet.position[d] += planet.velocity[d] * dt + 0.5 * dt*dt*acc[p][d];
			}

			// When the new position is set, calculate the next velocity by calculating the next force contribution
			// from the other planets for our planet's new position
			for (int p2 = p+1; p2 < planet_count; p2++){
				Planet &planet2 = planets[p2];
				GravitationalForce(dim, planet, planet2, F_next);
			}
			// Use the new acceleration to calculate the velocity of our planet
			for (int d = 0; i < dim; d++){
				acc_next[p][d] = F_next[d] * planet.mass;

				// Calculate the new position with VV
				planet.velocity[d] += 0.5 * dt*(acc[p][d] + acc_next[p][d]);
			}
		}
		// TODO: Fix this... "Pointer being freed was not allocated"
		//delete_matrix(acc);
		//delete_matrix(acc_next);
		//delete F; delete F_next;
    }

}

// Calculate the gravitational attraction between two planets
void System::GravitationalForce(int dim, Planet &p1, Planet &p2, double * &F){
	double r = p1.planetary_distance(p2);
	double r3 = r*r*r;

	// Calculate the relative distances and the force contributions in each direction
	for (int i = 0; i < dim; i++){
		double rel_dist = p1.position[i] - p2.position[i];
		F[i] -= G * p1.mass * p2.mass * rel_dist / r3;
	}
}

double ** System::setup_matrix(int cols, int rows){
	// Setting up a 2D "matrix" as an array
	double ** matrix;
	matrix = new double *[rows];

	// Allocate memory
	for (int i = 0; i < rows; i++){
		matrix[i] = new double[cols];
		for (int j = 0; j < rows; j++){
            matrix[i][j] = 0.0;
        }
	}
	return matrix;
}
void System::delete_matrix(double **matrix){
	// Deallocate memory of a 2D array
    for (int i = 0; i < planet_count; i++)
        delete [] matrix[i];
    delete [] matrix;
}
