
using namespace arma;
using namespace std;

void euler(mat a, mat v, mat r, int n){
    int yr = 5;
    double dt = (double) yr/ (double) n;

    double GM = 4 * pow(M_PI,2);

    //Forward Euler method
    for(int i=0; i < n-1; i++){
        double rad = sqrt(pow(r(i,0),2) + pow(r(i,1), 2));
        double a_abs = (GM)/pow(rad,2); //Acceleration
        
        a(i,0) = -r(i,0)/rad * a_abs; //Acceleration in x direction
        a(i,1) = -r(i,1)/rad * a_abs; //Acceleration in y direction
        
        v(i+1,0)= v(i,0) + a(i,0)*dt; //Velocity in x direction
        v(i+1,1)= v(i,1) + a(i,1)*dt; //Velocity in y direction

        r(i+1,0) = r(i,0) + v(i,0)*dt; //x position
        r(i+1,1) = r(i,1) + v(i,1)*dt; //y position
    }

    ofstream values_output;
    values_output.open("euler.dat");
    values_output << r;
}



void verlet(mat a, mat &v, mat &r, int n){
    int yr = 5;
    double dt = (double) yr/ (double) n;

    double GM = 4 * pow(M_PI,2);

    //Verlet method
    for(int i=0; i < n-1; i++){
        double rad = sqrt(pow(r(i,0),2) + pow(r(i,1), 2));
        double a_abs = (GM)/pow(rad,2); //Acceleration
        
        a(i,0) = -r(i,0)/rad * a_abs; //Acceleration in x direction
        a(i,1) = -r(i,1)/rad * a_abs; //Acceleration in y direction
        
        r(i+1, 0) = r(i,0) + v(i,0)*dt + 0.5*a(i,0)*dt*dt;
        r(i+1, 1) = r(i,1) + v(i,1)*dt + 0.5*a(i,1)*dt*dt;

        double rad_new = sqrt(pow(r(i+1,0),2) + pow(r(i+1,1), 2));
        double a_abs_new = (GM)/pow(rad_new,2); //Acceleration

        double ax = -r(i+1,0)/rad_new * a_abs_new; //Acceleration in x direction
        double ay = -r(i+1,1)/rad_new * a_abs_new; //Acceleration in y direction

        v(i+1,0) = v(i,0) + (ax+a(i,0))*dt/2;
        v(i+1,1) = v(i,1) + (ay+a(i,1))*dt/2;
    }


    ofstream values_output;
    values_output.open("verlet.dat");
    values_output << r;
}