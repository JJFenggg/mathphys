
// v = a = 1, u(x,t=0) = Phi(x)
// u(x,t) = 0.5*Phi(x-t) + 0.5*Phi(x+t)
// u(x,t) = \sum_n [ Cn cos( n pi t ) + Dn sin( n pi t )  ] sin( n pi x )
// utt = uxx
// u(x,t=0) = \sum_n Cn sin( n pi x ) = Phi(x)
// Cn = 2 \int^1_0 sin( n pi x ) Phi(x) dx, Dn = 0
// u(x,t) = 0.5*Phi(x-t) + 0.5*Phi(x+t) = \sum_n Cn cos( n pi t ) sin( n pi x )

#include<iostream>
using namespace std;

#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

double Phi(double x){ // equals varphi(x), the initial shape of the rope
	if( x>0 && x<0.5 ) return 1 - cos( 4 * M_PI * x );
	else return 0;
}

double psi(double x){ // initial velocity of the rope
	if( x>0 && x<0.5 ) return - 4 * M_PI * sin( 4 * M_PI * x );
	else return 0;
}

void CalCD( double (*varphi)(double ), double (*psi)(double), int nmax, double *C, double *D, int Nh ){
	double h = 1.0 / Nh, z1, z2, x;
	for(int n=1;n<=nmax;n++){
		z1 = 0; z2 = 0;
		for(int j=0;j<Nh;j++){
			x = (j+0.5)*h;
			z1 += 2*varphi(x)*sin( n * M_PI * x ) * h;
			z2 += 2.0 / n / M_PI * psi(x) * sin( n * M_PI * x ) * h;
		}
		C[n] = z1; D[n] = z2;
	}
}	

void PrintData( double (*Phi)(double), int nmax, double *C, double *D, int Nx, int Nt ){
	double h = 1.0 / Nx, z, x, t, dt = 0.5 / Nt, X, u;
	stringstream strm;
	// print data of Phi
	ofstream fout("output/Phi.txt");
	for(int i=0;i<=Nx;i++){// totally 2 + Nt columns
		x = i*h;
		fout<<x<<"  ";
		for(int m=0; m<= Nt; m++){
			t = m * dt;
			fout << Phi( x - t ) << "  ";
		}
		fout<<endl;
	}
	fout.close();
	
	// print data of un
	string file1 = "output/u", filen, fileu;
	for(int n = 1; n <= nmax; n++){
		strm.clear(); strm << n; strm >> filen;
		fileu = file1 + filen + ".txt";
		fout.open(fileu);
		for(int i=0;i<=Nx;i++){// totally 2 + Nt columns
			x = i*h; X = sin( n * M_PI * x );
			fout<<x<<"  ";
			for(int m=0; m<= Nt; m++){
				t = m * dt;
				fout<<( C[n] * cos( n* M_PI * t ) + D[n] * sin(n*M_PI*t) ) * X<<"  ";
			}
			fout<<endl;
		}
		fout.close();
	}
	// print data of Un		
	string file2 = "output/U", fileU;
	for(int N = 0; N <= nmax; N++){
		strm.clear(); strm << N; strm >> filen;
		fileu = file2 + filen + ".txt";
		fout.open(fileu);
		for(int i=0;i<=Nx;i++){// totally 2 + Nt columns
			x = i*h; fout<<x<<"  ";
			for(int m=0; m<= Nt; m++){
				t = m * dt;
				u = 0;
				for(int n=1;n<=N;n++){
					u += ( C[n] * cos( n* M_PI * t ) + D[n] * sin(n*M_PI*t) ) * sin( n * M_PI * x );
				}
				fout<< u <<"  ";
			}
			fout<<endl;
		}
		fout.close();
	}
}

void GnrPlt( int N, int Nt ){

	string file1 = "output/U", file2 = "output/u", fileN, filen;
	stringstream strm; strm.clear(); strm << N; strm >> fileN;
	string fileplt = file1 + fileN + ".plt";
	string filegif = file1 + fileN + ".gif";
	string fileU = file1 + fileN + ".txt", fileu;
        ofstream fp( fileplt );
        fp << " set term gif animate delay 10 \n";
        fp << " set output \""<< filegif <<"\"\n";
	fp << " do for [i=2:"<<Nt+2<<"]{\n";
	fp << " \t set yrange [-2.2:2.2]\n";
        fp << " \t plot \""<<fileU<<"\" u 1:i w l lw 3 lc \"blue\" title \" sum u_i\",";
	for( int n = 1; n<=N; n++ ){
		strm.clear(); strm << n; strm >> filen;
		fileu = file2 + filen + ".txt";
		fp << "\""<<fileu<<"\" u 1:i w l lw 1 title \"u"<<n<<"\",";
	}
	fp << "\"output/Phi.txt\" u 1:i w l lw 3 lc \"red\" title \"u(x,t)\" \n";
	fp << " }\n";
	fp << " set output ";
        fp.close();
}

void standingwave(int nmax, int Nx, int Nt){
	double *C = new double [ 1 + nmax ];
	double *D = new double [ 1 + nmax ];
	CalCD( Phi, psi, nmax, C, D, Nx );	
	//cout<<"C:"; for(int i=1;i<=nmax;i++)cout<<C[i]<<","; cout<<endl;
	//cout<<"D:"; for(int i=1;i<=nmax;i++)cout<<D[i]<<","; cout<<endl;
	PrintData( Phi, nmax, C, D, Nx, Nt ); 
	for(int N = 0; N <= nmax; N ++ )
		GnrPlt( N, Nt );

	delete [] C; delete [] D;
}
		
