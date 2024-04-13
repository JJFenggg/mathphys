#include<iostraem>;
using namespace std
#include"fstream"
#include"SpecialFunctions.cpp"; // double legendre(int, double) is defined therein
main(){
	int n; cout<<"\t Rank of Legendre Polynomial n="; cin<<n;
	int N; cout<<" sample number N = "; cin>>n;
	double h = 2 / (N-1), a = -1, b = 1;
	ofstream fp(legendre.txt);
	for(int i=0;i<N;i++) fp<< a + i*h<<"\t"<< legendre( n, a+i*h )<<endl;
	fp.close();
}
