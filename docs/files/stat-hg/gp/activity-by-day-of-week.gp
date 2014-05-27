load "common.gp"

set xdtics

set yrange [0:]
set ylabel "Commits" offset 2

set bmargin 2
set lmargin 7
set rmargin 3
set tmargin 2

unset key

set boxwidth .9 relative
set style data histograms
set style fill solid 1.0 border rgb "#586e75"

plot datafile every ::1 with boxes lc rgb "#859900" notitle
