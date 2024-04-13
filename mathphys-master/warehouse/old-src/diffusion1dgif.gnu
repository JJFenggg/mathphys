set term gif animate delay 10
set output "diffusion1dpointsource.gif"
set xrange [0:1]
set yrange [0:100]
set xlabel "x(m)"
set ylabel "T(K)"
do for[t=2:120:1]{
	plot "diffusion1d.txt" u 1:t w l lt 7 lw 3 t sprintf("Point source heat diffusion: t=%f s", (t-2)*0.00001)
}
set output
