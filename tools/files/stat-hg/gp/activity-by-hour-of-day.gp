load "common.gp"

set xrange [-1:24]

set xlabel "Hour"
set ylabel "Commits" offset 1

set bmargin 4
set lmargin 6
set rmargin 3
set tmargin 2

unset key

set boxwidth .9 relative
set style fill solid 1.0 border rgb "#586e75"
set style data histograms

plot datafile every ::1 using 2:xticlabels(1) with boxes lc rgb "#b58900" notitle
