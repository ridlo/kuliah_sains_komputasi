set yrange [-1:45]
set xlabel "Number of iteration"
set ylabel "Fitness - f(x)"
plot "best.txt" u 1:3 w l, "best-pop.txt" u 1:3 w l
