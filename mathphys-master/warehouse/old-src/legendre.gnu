set term png
set output "legendre2.png"

f(n,x) = n==0 ? 1 : ( (n==1) ? x: ( x*f(n-1,x) + (n-1)*( x*f(n-1,x) - f(n-2,x) )/n ) )

g(n,x) = f(n, cos(x))

set yrange [-1:1.2]
set key right bottom
plot [-1:1] f(0,x) w l lw 3 t "P_0(x)", \
f(1,x) w l lw 3 t "P_1(x)", \
f(2,x) w l lw 3 t "P_2(x)", \
f(3,x) w l lw 3 t "P_3(x)", \
f(4,x) w l lw 3 t "P_4(x)"

#plot [0:3.14159] g(0,x), g(1,x), g(2,x), g(3,x), g(4,x)
