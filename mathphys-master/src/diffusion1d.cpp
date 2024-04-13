#include<iostream>
using namespace std;
#include<fstream>
#include<cmath>
#include<stdlib.h>

/*
 * TridiagLinear:       Solve linear equations Ax=r, where A has a tridiagonal form:
 *                      b0      c0
 *                      a1      b1      c1
 *                      0       a2      b2      c2
 *                      ...     ...     ...     ...
 *                      ...     ...     ...     ...
 *                                      a_{n-1} b_{n-1}
 *
 *                      The solution is stored in u
 */
void TridiagLinear( int n, double *a, double *b, double *c, double *u, double *r ){

        int j;
        double *gamma = new double [n];
        u[0] = r[0]/b[0];
        gamma[0] = 0;
        for(j=1;j<n;j++){
                gamma[j] = c[j-1]/(b[j-1] - a[j-1]*gamma[j-1]);
                u[j] = ( r[j] - a[j]*u[j-1] )/(b[j] - a[j]*gamma[j]);
        }
        for(j=n-2;j>=0;j--){
                u[j] -= gamma[j+1]*u[j+1];
        }
        delete [] gamma;
}

/*
 * diffusion1d(...)		solves a 1-dimensional diffusion equation
 * 		\partial^2 u / \partial x^2 = \partial u / \partial t
 * 		and prints u(*,t_j) into "diffusion1d.txt"
 * double xa
 * double xb			x zone [xa, xb]
 * double (*g_initial)(...)	u(x, t=0)
 * double ta
 * double tb			t zone [ta, tb]
 * double (*boundary_a)(...)	u(xa, t)
 * double (*boundary_b)(...)	u(xb, t)
 * int Nx			grid point number in (xa,xb)
 * int Nt			grid point number in (ta,tb)
 */
void diffusion1d( double xa, double xb, double (*g_initial)(double x), double ta, double tb, double (*boundary_a)(double t), double (*boundary_b)(double t), int Nx, int Nt){

	int i, j;
	double dx, dt, alpha;
	double *u = new double [Nx];
	double *unext = new double [Nt];
	double *a = new double [Nx];// tridiagonal matrix
	double *b = new double [Nx];
	double *c = new double [Nx];

	dx = (xb-xa)/(Nx+1);// [xa, xb] is divided into Nx+1 small zones
	dt = (tb-ta)/Nt;// [ta, tb] is divided into Nt steps
	alpha = dt/dx/dx;
	for(i=0;i<Nx;i++){// initialize tridiagonal matrix
		a[i] = -alpha;
		b[i] = 1 + 2*alpha;
		c[i] = -alpha;
	}
	for(i=0;i<Nx;i++){//initial u(x, t=0)
		u[i] = g_initial(xa + (i+1)*dx);
	}
	ofstream fp("output/diffusion1d.txt");// (Nt+1) * ( Nx+2 )
	fp<< xa<<"\t"; for(i=0;i<Nx;i++)fp<< xa + (i+1)*dx<<"\t"; fp<< xb<<endl;
	for(i=0;i<Nx+2;i++)fp<< g_initial(xa + i*dx) <<"\t"; fp<<endl;
	for(j=1;j<=Nt;j++){
		// print u(x0, t), u(x1, t), ... to file, as a line
		fp<< boundary_a( ta+ (j-1)*dt)<<"\t"; 
		for(i=0;i<Nx;i++)fp<<u[i]<<"\t"; 
		fp<< boundary_b( ta+ (j-1)*dt)<<"\t";
		fp<<endl;
		// calculate u(x0, t+dt), u(x1, t+dt), ...
		u[0] += alpha * boundary_a( ta + j*dt);
		u[Nx-1] += alpha * boundary_b( ta + j*dt);
		TridiagLinear( Nx, a, b, c, unext, u);
		// update u[]
		for(i=0;i<Nx;i++) u[i] = unext[i];
	}
	fp.close();

	double **data = new double * [Nt +1];
	for(int i=0;i<Nt+1;i++){
		data[i] = new double [Nx+2];
	}

	ifstream fin("output/diffusion1d.txt"); // transpose the matrix u_{i,j}
	for(int i=0;i<Nt+1;i++)
		for(int j=0;j<Nx+2;j++)
			fin>>data[i][j];
	fin.close();

	fp.open("output/diffusion1dgif.txt");
	for(int j=0;j<Nx+2;j++){
		for(int i=0;i<Nt+1;i++)
			fp<<data[i][j]<<"\t";
		fp<<endl;
	}
	fp.close();


	for(int i=0;i<Nt+1;i++) delete [] data[i];
	delete [] data;

	delete [] c;
	delete [] b;
	delete [] a;
	delete [] u;
	delete [] unext;

	fp.open("output/diffusion1d.gnu");
	fp<<" set term png \n \
set output \"output/diffusion1d.png\" \n \
set xrange [0:1000] \n \
set xlabel \"x (m)\" font \"Arial,15\" \n \
unset xtics \n \
set xtics (\"0\" 0, \"0.2\" 200, \"0.4\" 400, \"0.6\" 600, \"0.8\" 800, \"1\" 1000) \n\
unset ytics  \n\
set ylabel \"t (s)\" font \"Arial,15\" \n\
set yrange [0:1000] \n\
set title \"Heat map: 1 dimensional diffusion\" font \"Arial,20\" \n\
plot \"output/diffusion1d.txt\" matrix w image ";
	fp.close();
//set ytics (\"0\" 0, \"0.1\" 200, \"0.2\" 400, \"0.3\" 600, \"0.4\" 800, \"0.5\" 1000) \n\

	cout<<" gnuplot output/diffusion1d.gnu "<<endl;
	system("gnuplot output/diffusion1d.gnu");
	cout<<" output/diffusion1d.png has been generated. \n";
	system("eog output/diffusion1d.png &");

	fp.open("output/diffusion1dgif.gnu");
	fp<<" set term gif animate delay 1\nset output \"output/diffusion1d.gif\"\nset xrange [0:1]\nset yrange [0:100]\nset xlabel \"x(m)\"\nset ylabel \"T(K)\"\ndo for[t=2:"<<1+Nt<<":1]{\n	plot \"output/diffusion1dgif.txt\" u 1:t w l lt 7 lw 3 t sprintf(\" t = %f s\", (t-2)*"<<(tb-ta)/Nt<<" ) \n}\nset output\n ";
	fp.close();

	cout<<" gnuplot output/diffusion1dgif.gnu "<<endl;
	system("gnuplot output/diffusion1dgif.gnu");
	cout<<" output/diffusion1d.gif has been generated. \n";
	system("eog output/diffusion1d.gif &");
	
}
