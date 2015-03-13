load "common.gp"

set xdata time
set format x "%b-%y"

set yrange [*:*]
set ytics nomirror
set ylabel "File count" offset 1

set y2range [*:*]
set y2tics nomirror
set y2label "Lines per file" offset -1 rotate by -90

set lmargin 8

set key width -5 height .5

plot datafile every ::1 using 2:5 title "File count" with lines lw 2 lc rgb "#dc322f", \
 "" every ::1 using 2:6 title "Lines per file" with lines lc rgb "#6c71c4" lw 2 axes x1y2
