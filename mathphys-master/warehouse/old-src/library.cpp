
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
using namespace std;

/*
 * Given [a,b], returns abscissas x[] and weights w[], based on zeros of P_n(x)
 * Modified from Numerical Recipes
 */
void GauLeg(double a, double b, int n, double *x, double *w){

        double eps=1E-14;
        int m,j,i;
        double z1,z,xm,xl,pp,p3,p2,p1;

        m=(n+1)/2;
        xm=0.5*(a+b);
        xl=0.5*(b-a);
        for(i=0;i<m;i++){
                z=cos(M_PI*(i+0.75)/(n+0.5));//starting guess
                do{                     //Newton's method to get the ith zero
                        p1=1.0;         // P_0
                        p2=0.0;
                        for(j=0;j<n;j++){
                                p3=p2;  // P_{j-1}
                                p2=p1;  // P_{j}
                                p1= z*p2 + (z*p2-p3)*j/(j+1);
                                // P_{j+1},based on recurrence relation:
                                // (j+1)P_{j+1} = (2j+1)P_j - j P_{j-1}
                        }
                        pp=n*(z*p1-p2)/(z*z-1); // P'n(x_i), based on
                                    // (1-x^2)P'_n(x) = n P_{n-1}(x) - nxP_n (x)
                        z1=z;
                        z=z1-p1/pp; // Newton's method: s = x - f(x)/f'(x)
                }while(fabs(z-z1)>eps);
                x[i]=xm-xl*z;
                x[n-1-i]=xm+xl*z;
                w[i] = 2.0*xl/((1.0-z*z)*pp*pp); // formula of weights:
                                    // w[i] = 2/(1-x_j^2)/P'n(x_j)^2 for [-1,1]
                                    // multiplied by xl, for [a,b]
                w[n-1-i]=w[i];
        }
}
