set term gif animate delay 1
set output "wave1d.gif"
set xrange [0:1]
set yrange [-2:2.5]
set xlabel "x(m)"
set ylabel "y(m)"
do for[t=2:801:1]{
	plot "wave1d.txt" u 1:t w l lw 3 t sprintf("string wave: v=1m/s, t=%f s", (t-2)*0.4/800)
}
set output
