/*
*	Main file for project 1
*	Collaborators: Benedicte Allum Pedersen, Fredrik Forr, Emil Broll
*/
#include <iostream>	// Input/output
#include <cmath>	// Math functions
#include <cstdlib> // atof function 

using namespace std; // Unwraps the iostream-functions

int main (int argc, char* argv[])
{
	if (argc < 2){
		return 0; // Exit if no argument is provided
	}

	// Convert the text from the second index of argv to an double
	double input = atof(argv[1]);
	double val = sin(input);

	// Print Hello Word and the sine shit
	cout << "Hello World, the sine of " << input << " is " << val << endl;

	return 0; // Success
}