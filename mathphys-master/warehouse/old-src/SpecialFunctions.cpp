
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
