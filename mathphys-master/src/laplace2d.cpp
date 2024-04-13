#include<iostream>
using namespace std;

#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

#define bg -200

// f(theta): default domain: [0,2pi]
double f( double theta ){
	/*
	if( theta < M_PI / 3 || theta > 5 * M_PI / 3 ) return 100;
	else return 0;
	*/
	return 100* cos( theta );
	//if( theta < M_PI ) return 100;
	//else return 0;
}

double gcos( double theta, int n ){
	if(n == 0) return 1 / sqrt( 2 * M_PI );
	else return cos( n * theta ) / sqrt( M_PI );
}

double gsin( double theta, int n ){
	return sin( n * theta ) / sqrt( M_PI );
}

// f(theta) \approx \sum_i [ a_i gcos + b_i gsin ], i=0,1,...,n
// calculate a_i, b_i
void calab( double (*f)(double ), int n, double * a, double * b, int N ){
	double h = 2*M_PI/N, z1, z2, x;
	for(int i=0;i<=n;i++){
		z1 = 0; z2 = 0;
		for(int j=0;j<N;j++){// rectangular quadrature
			x = (j + 0.5)*h;
			z1 += f(x)*gcos(x, i)*h;
			z2 += f(x)*gsin(x, i)*h;
		}
		a[i] = z1; b[i] = z2;
	}
}

double u( double r, double theta, int n, double * a, double * b ){
	if( r > 1 ) return bg;
	double y=0;
	for(int i=0;i<=n;i++)
		y += ( a[i] * gcos( theta, i ) + b[i] * gsin( theta, i ) ) * pow(r, i);
	return y;
}

// returns theta in [ - pi/2, 3pi/2 ]
void calrtheta( double x, double y, double & r, double & theta ){
	r = sqrt( x*x + y*y );
	if( fabs(x)<1E-6 && y >=0 ) theta = M_PI /2 ;
	else if( fabs(x)<1E-6 && y<0 ) theta = - M_PI /2 ;
	else{
		theta = atan( y/x );
		if( x<0 ) theta += M_PI;
	}
}

void GnrData( double xmin, double xmax, double ymin, double ymax, int N, int n, double * a, double * b, string filedata ){
	double dx = (xmax - xmin)/N;
	double dy = (ymax - ymin)/N;
	ofstream fp( filedata );
	double x, y, r, theta, T;
	for(int j=0;j<=N;j++){
		for( int i=0; i<=N; i++ ){
			x = xmin + i*dx; y = ymin + j*dy;
			calrtheta( x, y, r, theta );
			T = u( r, theta, n, a, b );
			fp << T <<" ";
		}
		fp<<endl;
	}
	fp.close();
}

// produce (N+1) x (N+1) grid data, and generate gnuplot script
void GnrPlt( double (*f)(double), int n, int N, string filedata, string fileplt, string filepng ){
	double * a = new double [ n+1 ];
	double * b = new double [ n+1 ];
	calab( f, n, a, b, 10000 );// 10000 is for quadrature accuracy
	GnrData( -1.1, 1.1, -1.1, 1.1, N, n, a, b, filedata );
	ofstream fp( fileplt );
	fp << " set term png \n";
	fp << " set output \""<< filepng <<"\"\n";
	fp << " unset border \n ";
	fp << " unset xtics \n ";
	fp << " unset ytics \n ";
	fp << " plot \""<<filedata<<"\" matrix w image \n";
	fp.close();
	delete [] a; delete [] b;
}

void laplace2d(){

	int n = 30, N=1000;
	string filedata = "output/laplace2d.txt", fileplt = "output/laplace2d.plt", filepng = "output/laplace2d.png";
	GnrPlt( f, n, N, filedata, fileplt, filepng );
}
