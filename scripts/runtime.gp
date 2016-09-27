reset
set ylabel 'numerical distribution'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'

plot [:][:0.0000003]'iteration.txt' using 2 with linespoints title 'iteration', \

