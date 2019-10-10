#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

/*
a og b er grensene på integralet men de er lambda :- O
*/

void gauss_legendre(double a, double b, double x[], double w[], int N)
{



}//End function

  int         m,j,i;
  double      z1,z,xm,xl,pp,p3,p2,p1;
  double      const  pi = 3.14159265359;
  double      *x_low, *x_high, *w_low, *w_high;
  double tol = 1.0E-10

  m  = (N + 1)/2;                             // roots are symmetric in the interval
  xm = 0.5 * (x2 + x1);
  xl = 0.5 * (x2 - x1);

  x_low  = x;                                       // pointer initialization
  x_high = x + N - 1;
  w_low  = w;
  w_high = w + N - 1;

  for(i = 1; i <= m; i++) {                             // loops over desired roots
     z = cos(pi * (i - 0.25)/(N + 0.5));

          /*
    ** Starting with the above approximation to the ith root
          ** we enter the mani loop of refinement bt Newtons method.
          */

     do {
        p1 =1.0;
  p2 =0.0;

      /*
    ** loop up recurrence relation to get the
          ** Legendre polynomial evaluated at x
          */

  for(j = 1; j <= n; j++) {
     p3 = p2;
     p2 = p1;
     p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3)/j;
  }

    /*
    ** p1 is now the desired Legrendre polynomial. Next compute
          ** ppp its derivative by standard relation involving also p2,
          ** polynomial of one lower order.
          */

  pp = N * (z * p1 - p2)/(z * z - 1.0);
  z1 = z;
  z  = z1 - p1/pp;                   // Newton's method
} while(fabs(z - z1) > tol);

         /*
   ** Scale the root to the desired interval and put in its symmetric
         ** counterpart. Compute the weight and its symmetric counterpart
         */

     *(x_low++)  = xm - xl * z;
     *(x_high--) = xm + xl * z;
     *w_low      = 2.0 * xl/((1.0 - z * z) * pp * pp);
     *(w_high--) = *(w_low++);
  }

  /*
  //legendre polynomene:
  double r, s, t;
  int m;
  r = 0; s = 1;

  for (m=0; m < N; m++)
  {
    t = r; r = s;
    s = double((2*m+1)*x*r) - double(m*t);
    s /= (m+1);
  }
  */
