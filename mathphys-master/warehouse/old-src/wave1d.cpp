#include<iostream>
using namespace std;
#include<fstream>
#include<cmath>
#include<string>

void wave1d(	double xa, int nx, double dx, 
		double (*boundary1)(double t), double (*boundary2)(double t), 
		int nt, double dt, double (* u_initial)(double x), 
		string file ){
	
	int i,j;
	double alpha = dt*dt/dx/dx;

	double *u_old = new double [nx]; // u_{i-1}
	double *u = new double [nx]; // u_i
	double *u_new = new double [nx]; // u_{i+1}

	u_old[0] = boundary1(0);
	u_old[nx-1] = boundary2(0);
	for(i=1;i<nx-1;i++) u_old[i] = u_initial( xa + i*dx);
	
	u[0] = boundary1(dt);
	u[nx-1] = boundary2(dt);
	for(i=1;i<nx-1;i++) u[i] = (1-alpha)*u_old[i] + alpha/2*( u_old[i+1] + u_old[i-1] );

	ofstream fp(file);
	if(!fp){
		cout<<"error: failed to open "<<file<<endl;
		exit(1);
	}
	for(i=0;i<nx;i++)fp<<u_old[i]<<"\t"; fp<<endl;
	for(i=0;i<nx;i++)fp<<u[i]<<"\t"; fp<<endl;

	/* for test only
	for(i=0;i<nx;i++)cout<<u_old[i]<<"\t"; cout<<endl;
	for(i=0;i<nx;i++)cout<<u[i]<<"\t"; cout<<endl;
	*/

	for(j=2;j<=nt;j++){
		u_new[0] = boundary1( j*dt);
		u_new[nx-1] = boundary2( j*dt);
		for(i=1;i<nx-1;i++)
			u_new[i] = (2-2*alpha)*u[i] + alpha * u[i+1] + alpha* u[i-1] - u_old[i];
		for(i=0;i<nx;i++)fp<<u_new[i]<<"\t"; fp<<endl;
		//for(i=0;i<nx;i++)cout<<u_new[i]<<"\t"; cout<<endl;
		
		for(i=0;i<nx;i++){
			u_old[i] = u[i];
			u[i] = u_new[i];
		}
	}
	fp.close();
}

double u_initial(double x){
	if( x>=0.4 && x<=0.6 ) return 2;
	else return 0;
	/*
	if( x>= 0.4 && x<=0.5 ) return 20*(x-0.4);
	else if( x>=0.5 && x<=0.6 ) return 20*(0.6-x);
	else return 0;
	*/
	//if(x>0.5 && x<1) return sin(4*M_PI*x);
	//else return 0;
	//return sin( 3* M_PI * x );
	//return 0;
	
}

double boundary1(double t){
	//return sin(10*M_PI*t);
	//return sin(10*M_PI*t);
	//if( t< 1.0/10 ) return sin(10*M_PI*t);
	//else return 0;
	return 0;
}

double boundary2(double t){
	return 0;
}

int main(){

	int i,j,nx=400;
	double xa=0, xb=1;
	double dx = (xb-xa)/(nx-1);
	int nt=800;
	double ta=0, tb=0.4;
	double dt = (tb-ta)/(nt-1);
	double **matrix;

	string file = "wave1d.txt";

	wave1d( 0, nx, dx, boundary1, boundary2,
		nt, dt, u_initial, file);

	// transpose the data matrix
	matrix = new double *[nt+1];
	for(i=0;i<nt+1;i++) matrix[i] = new double [nx];

	ifstream fp1( file );
	for(i=0;i<nt+1;i++)
		for(j=0;j<nx;j++)
			fp1>> matrix[i][j];
	fp1.close();

	ofstream fp2( file );
	for(j=0;j<nx;j++){
		fp2<< xa + j*dx <<"\t";
		for(i=0;i<nt+1;i++)
			fp2<< matrix[i][j]<<"\t";
		fp2<<endl;
	}
	fp2.close();

	return 0;
}
