load "common.gp"

set xdata time
set format x "%b-%y"

set ytics
set yrange [0:100]
set ylabel "%" offset 2

set bmargin 4
set lmargin 6
set rmargin 2
set tmargin 1

set key width -5 height .5

plot datafile every ::1 using 2:(100.*$4/($4+$5+$6)) with filledcurves x1 lc rgb "#268bd2" title "Modified lines", \
 "" every ::1 using 2:(100.*($4+$5)/($4+$5+$6)):(100.*($4)/($4+$5+$6)) with filledcurves lc rgb "#859900" title "Added lines", \
 "" every ::1 using 2:(100.):(100.*($4+$5)/($4+$5+$6)) with filledcurves lc rgb "#dc322f" title "Deleted lines"
