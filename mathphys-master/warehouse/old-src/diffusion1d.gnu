set term png
set output "../diffusion1d.png"
set xrange [0:1000]
set xlabel "x (m)" font "Arial,15"
unset xtics
set xtics ("0" 0, "0.2" 200, "0.4" 400, "0.6" 600, "0.8" 800, "1" 1000)
unset ytics
set ytics ("0" 0, "0.1" 200, "0.2" 400, "0.3" 600, "0.4" 800, "0.5" 1000)
set ylabel "t (s)" font "Arial,15"
set yrange [0:1000]
set title "Heat map: 1 dimensional diffusion" font "Arial,20"
plot "diffusion1d.txt" matrix w image
