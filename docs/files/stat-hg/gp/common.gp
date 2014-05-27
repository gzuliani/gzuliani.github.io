set datafile separator "|"
set timefmt "%Y-%m-%d %H:%M"

myfont = "Cambria,10"
xfont = myfont
yfont = myfont
keyfont = myfont

set tics tc rgb "#586e75" font xfont front

set xtics out nomirror
set xlabel tc rgb "#586e75" font xfont

set ylabel tc rgb "#586e75" font yfont
set y2label tc rgb "#586e75" font yfont

set key tc rgb "#586e75" font keyfont box opaque below

set bmargin 4
set lmargin 7
set rmargin 7
set tmargin 1

set border lc rgb "#586e75"

set term pngcairo background "#fdf6e3" size 800,400

