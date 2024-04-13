
#include<iostream>
using namespace std;

#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

#include"fourier_series.h"
#include"standingwave.h"
#include"laplace2d.h"
#include"diffusion1d.h"

double Tleft(double t){// temperature of left boundary
        return 100;
}

double Tright(double t){// temperature of right boundary
        return 0;
}

double Tinitial(double x){

        return 0;
}

int main(){

	int nmax; stringstream strm; string line, mode;
	cout<<"-------------------------------------------------------------\n";
	cout<<"mathphys1.0  by Yi Lu(路毅) luyi@qfnu.edu.cn     \n \
		mathematical physics pedagogical codes for demonstration \n";
	cout<<"-------------------------------------------------------------\n";
	cout<<"         Mode Options "<<endl;
	cout<<" (fourier) Fourier Series Expansion of a given function, on [-1,1] \n";
	cout<<" (standingwave) 1 dimensional standing wave decomposition \n";
	cout<<" (laplace2d) solve 2-dim laplace equation with circular boundary \n";
	cout<<" (diffusion1d) solve 1-dim diffusion equation. \n";
        cout<<" \t Mode = ? ";
        getline(cin, line); strm.str(line); strm >> mode;
        cout<<" So mode = "<<mode<<endl;

	if( mode == "fourier" ){
		cout<<"---------------------------- Fourier Series Expansion ---------------------------\n";
		cout<<" On [-1,1], approximate F(x) with finite fourier series: \n \
			Fn(x) = a0 f0(x) + a1 f1(x) + ... + an fn(x) + b1 g1(x) + ... + bn gn(x), \n";
		cout<<" where f0(x) = 1/sqrt(2), fn(x) = cos( n pi x ), gn(x) = sin( n pi x ), n automatically runs from 0, 1, 2 to nmax. \n\tnmax =";
		getline(cin, line); strm.clear(); strm.str(line); strm >> nmax;
		cout<<" So nmax =  "<<nmax<<". Got it. Calculating...\n";

		fourier_series( nmax );
		cout<<"---------------------------- Finished -------------------------------------------\n";
	}
	else if( mode == "standingwave" ){
		int nmax = 10, Nx = 100, Nt = 100;
		standingwave( nmax, Nx, Nt );
	}
	else if( mode == "laplace2d" ){
		laplace2d();
	}
	else if( mode == "diffusion1d" ){
		cout<<" On x = [0,1], diffusion process is simulated, with given initial temperature defined by Tinitial() in src/main.cpp, left and right boundary conditions defined by Tleft(), Tright."<<endl;
		diffusion1d(0, 1, Tinitial, 0, 0.3, Tleft, Tright, 1000, 1000);
	}

	return 0;
}
