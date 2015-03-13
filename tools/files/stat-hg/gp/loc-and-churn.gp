load "common.gp"

set xdata time
set format x "%b-%y"

set yrange [*:*]
set format y "%.0s%c"
set ytics nomirror
set ylabel "Lines of code" offset 1

set y2range [*:*]
set format y2 "%.0s%c"
set y2tics nomirror
set y2label "Lines touched" offset -1 rotate by -90

set key width -5 height .5

plot datafile_loc every ::1 using 2:4 title "Lines of code" with lines lw 2 lc rgb "#dc322f", \
datafile_churn every ::1 using 2:($4+$5+$6) title "Lines touched" with impulses lc rgb "#6c71c4" lw 2 axes x1y2
