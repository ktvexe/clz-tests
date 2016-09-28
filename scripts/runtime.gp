reset
set xlabel 'numerical distribution'
set ylabel 'time(cycles)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set xtic 2000
plot [:][:500]'iteration.txt' using 2 with linespoints title 'iteration',\
'byte.txt' using 2 with linespoints title 'byte',\
'binary.txt' using 2 with linespoints title 'binary',\
'recursive.txt' using 2 with linespoints title 'recursive',\
'harley.txt' using 2 with linespoints title 'harley'

