#include<iostream>
using namespace std;

#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

// default domain: [-1,1]

// 1/sqrt(2), cos(x), cos(2x), ..., cos(nx), ...
double f( double x, int n ){
	if( n==0 ) return 1/sqrt(2);
	else return cos(n*M_PI*x);
}

//     sin(x), sin(2x), ..., sin(nx), ...
double g( double x, int n ){
	return sin( n*M_PI*x);
}

/*
 * calculate innerproducts a[i] = (F, fi), b[i] = (F, gi)
 */
void Calab( double (*F)(double ), int n, double * a, double * b, int N ){
	double h = 2.0/N, z1, z2, x;
	for(int i=0;i<=n;i++){
		z1 = 0; z2 = 0;
		for(int j=0;j<N;j++){
			x = -1 + (j + 0.5)*h;
			z1 += F(x)*f(x, i)*h;
			z2 += F(x)*g(x, i)*h;
		}
		a[i] = z1; b[i] = z2;
	}
}

// fileDelta: plot Delta(x,n) = F(x) - \sum^n_j{ a[j] f(x,j) + b[j] g(x,j) }
void GnrPlt( double (*F)(double ), int N, string file_series, string file_Delta ){ 
	double * a = new double [ N+1 ];
	double * b = new double [ N+1 ];
	Calab( F, N, a, b, 10000 );

	ofstream fp( file_series );
	double h = 2.0/1000, z, x;
	for( int i=0; i<=1000; i++ ){
		x = -1 + i*h; fp << x << "  "<<F(x)<<"  ";
		for(int n=0;n<=N;n++){
			z = 0;
			for(int j=0;j<=n;j++){
				z += a[j] * f( x, j ) + b[j] * g( x, j );
			}
			// z(xi) = \sum_j { a[j] f( xi, j ) + b[j] g( xi, j) }
			fp << z <<"  ";
		}
		fp<<endl;
	}
	fp.close();

	fp.open( file_Delta );
	for( int i=0; i<=1000; i++ ){
		x = -1 + i*h; fp << x << "  ";
		for(int n=0;n<=N;n++){
			z = 0;
			for(int j=0;j<=n;j++){
				z += a[j] * f( x, j ) + b[j] * g( x, j );
			}
			// z(xi) = \sum_j { a[j] f( xi, j ) + b[j] g( xi, j) }
			fp << F(x) - z <<"  ";
		}
		fp<<endl;
	}
	fp.close();
	
	fp.open( "output/series.plt" );
	fp << " set term png \n";
	fp << " set output \"output/series.png\" \n";
	fp << " plot \""<<file_series<<"\" u 1:2 w l lw 3 lc \"red\" t \"F(x)\", ";
	for(int n=0;n<=N;n++){
		if( n*10 % (N*10/4) == 0 ){
			if(n<N) fp<< "\"\" u 1:"<<n+3<<" w l t \"F"<<n<<"\",";
			else fp<< "\"\" u 1:"<<n+3<<" w l lw 2 lc \"black\" t \"F"<<n<<"\"";
		}
	}
	fp.close();

	system("gnuplot output/series.plt");
	system("eog output/series.png &");

	fp.open( "output/Delta.plt" );
	fp << " set term png \n";
	fp << " set output \"output/Delta.png\" \n";
	fp << " plot \""<<file_Delta<<"\" u 1:2 w l t \"Delta0(x)\", ";
	for(int n=1;n<=N;n++){
		if( n*10 % (N*10/4) == 0 ){
			if(n<N) fp<< "\"\" u 1:"<<n+2<<" w l t \"Delta"<<n<<"(x)\",";
			else fp<< "\"\" u 1:"<<n+2<<" w l t \"Delta"<<n<<"(x)\"";
		}
	}
	fp.close();

	system("gnuplot output/Delta.plt");
	system("eog output/Delta.png &");

	delete [] a; delete [] b;
}

double F(double x ){
	return x*x;
}

void fourier_series(int nmax ){
	GnrPlt( F, 20, "output/series.txt", "output/Delta.txt"  );
}
