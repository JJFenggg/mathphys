#include<iostream>
using namespace std;
#include<fstream>
#include<cmath>

#include"library.h"

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
	ofstream fp("diffusion1d.txt");// (Nt+1) * ( Nx+2 )
	fp<< xa<<"\t";
	for(i=0;i<Nx;i++)fp<< xa + (i+1)*dx<<"\t";
	fp<< xb<<endl;
	for(i=0;i<Nx+2;i++)fp<< g_initial(xa + i*dx) <<"\t"; fp<<endl;
	for(j=1;j<=Nt;j++){
		fp<< boundary_a( ta+ (j-1)*dt)<<"\t";
		for(i=0;i<Nx;i++)fp<<u[i]<<"\t"; 
		fp<< boundary_b( ta+ (j-1)*dt)<<"\t";
		fp<<endl;
		u[0] += alpha * boundary_a( ta + j*dt);
		u[Nx-1] += alpha * boundary_b( ta + j*dt);
		TridiagLinear( Nx, a, b, c, unext, u);
		for(i=0;i<Nx;i++) u[i] = unext[i];
	}
	fp.close();

	double **data = new double * [Nt +1];
	for(int i=0;i<Nt+1;i++){
		data[i] = new double [Nx+2];
	}

	ifstream fin("diffusion1d.txt");
	for(int i=0;i<Nt+1;i++)
		for(int j=0;j<Nx+2;j++)
			fin>>data[i][j];
	fin.close();

	fp.open("diffusion1d.txt");
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
}

double Tleft(double t){// temperature of left boundary
	return 0;
}

double Tright(double t){// temperature of right boundary
	return 0;
}

double Tinitial(double x){
	if( 0.49 <= x && x <= 0.51 ) return 100;
	else return 0;
	//if(x<0.5) return x;
	//else return 1-x;
}

int main(){
	diffusion1d(0, 1, Tinitial, 0, 0.01, Tleft, Tright, 1000, 1000);
	return 0;
}
