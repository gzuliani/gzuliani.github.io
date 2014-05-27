load "common.gp"

set xdata time
set format x "%b-%y"

set yrange [0:24]
set ytics in 0,2
set ylabel "Hour" offset 1

unset key

plot datafile every ::1 using 1:(tm_hour(timecolumn(1)) + tm_min(timecolumn(1)) / 60) with points pt 7 lc rgb "#2aa198" notitle
