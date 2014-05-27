load "common.gp"

set xrange [0:23]
set xtics out 0,1 nomirror
set xlabel "Hour"

set yrange [0:6]
set ydtics

set bmargin 4
set lmargin 6
set rmargin 3
set tmargin 2

unset key

set style fill transparent

plot datafile every ::1 using 2:1:3 with points ps variable pt 7 lc rgb "#268bd2" notitle
