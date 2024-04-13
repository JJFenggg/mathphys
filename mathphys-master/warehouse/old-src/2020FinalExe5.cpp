#include<iostream>
using namespace std;
#include"fstream"

double legendre( int n, double x ){
        if( x<-1 || x>1 ){
                cout<<" invalid value x="<<x<<" for legendre(n,x), x should be in [-1,1]"<<endl;
                exit(1);
        }
        double y = 1, z=x, temp;
        for(int i=1;i<=n-1;i++){
                temp = x * z +  i * ( x * z - y ) / (i+1);
                y = z; z = temp;
        }
        return z;
}

int main(){
	int n; cout<<"\t n="; cin>>n;
	int N; cout<<" sample number = "; cin>>N;
	double h = 2.0 / (N-1), a = -1, b = 1;

	ofstream fp("legendre.txt");
	for(int i=0;i<N;i++)
		fp<< a + i*h<<"\t"<< legendre( n, a+i*h )<<endl;
	fp.close();

	return 0;
}
