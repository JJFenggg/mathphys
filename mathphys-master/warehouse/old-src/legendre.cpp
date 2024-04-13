#include<iostream>
using namespace std;
#include"fstream"

#include"SpecialFunctions.cpp"

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
