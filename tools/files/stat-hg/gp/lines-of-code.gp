load "common.gp"

set xdata time
set format x "%b-%y"

set yrange [*:*]
set format y "%.0s%c"
set ytics nomirror

unset key

plot datafile every ::1 using 2:4 title "Lines of code" with lines lw 2 lc rgb "#dc322f"
