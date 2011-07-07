set xlabel "{/Times-Italic r/D}"
set ylabel "{/Times-Italic g}({/Times-Italic r})"
set xrange [1.0:5.0]
#set yrange [0:3.0]
#set ytics 0,0.2
set style line 11 lc rgb "dark-red" lw 1.0 lt 1
set style line 12 lc rgb "dark-red" lw 0.5 lt 1 pointsize 0
set style line 21 lc rgb "red" lw 1.0 lt 1
set style line 22 lc rgb "red" lw 0.5 lt 1 pointsize 0
set style line 31 lc rgb "light-red" lw 1.0 lt 1
set style line 32 lc rgb "light-red" lw 0.5 lt 1 pointsize 0
set style line 41 lc rgb "coral" lw 1.0 lt 1
set style line 42 lc rgb "coral" lw 0.5 lt 1 pointsize 0
set style line 51 lc rgb "dark-orange" lw 1.0 lt 1
set style line 52 lc rgb "dark-orange" lw 0.5 lt 1 pointsize 0
set style line 61 lc rgb "orange" lw 1.0 lt 1
set style line 62 lc rgb "orange" lw 0.5 lt 1 pointsize 0
set style line 71 lc rgb "dark-yellow" lw 1.0 lt 1
set style line 72 lc rgb "dark-yellow" lw 0.5 lt 1 pointsize 0
set style line 81 lc rgb "yellow" lw 1.0 lt 1
set style line 82 lc rgb "yellow" lw 0.5 lt 1 pointsize 0
set style line 91 lc rgb "light-green" lw 1.0 lt 1
set style line 92 lc rgb "light-green" lw 0.5 lt 1 pointsize 0
set style line 101 lc rgb "green" lw 1.0 lt 1
set style line 102 lc rgb "green" lw 0.5 lt 1 pointsize 0
set style line 111 lc rgb "dark-green" lw 1.0 lt 1
set style line 112 lc rgb "dark-green" lw 0.5 lt 1 pointsize 0
set style line 121 lc rgb "blue" lw 1.0 lt 1
set style line 122 lc rgb "blue" lw 0.5 lt 1 pointsize 0
set style line 131 lc rgb "turquoise" lw 1.0 lt 1
set style line 132 lc rgb "turquoise" lw 0.5 lt 1 pointsize 0
set style line 141 lc rgb "violet" lw 1.0 lt 1
set style line 142 lc rgb "violet" lw 0.5 lt 1 pointsize 0
set style line 151 lc rgb "purple" lw 1.0 lt 1
set style line 152 lc rgb "purple" lw 0.5 lt 1 pointsize 0
set style line 16 lc rgb "#000000" lw 0.2 lt 1 pointsize 0.0
set style line 161 lc rgb "#000000" lw 0.2 lt 1 pointsize 0.0
set style line 162 lc rgb "#000000" lw 0.2 lt 4 pointsize 0.0
set style line 163 lc rgb "#000000" lw 0.2 lt 3 pointsize 0.0
set style line 164 lc rgb "#000000" lw 0.2 lt 2 pointsize 0.0
set style line 165 lc rgb "#000000" lw 0.2 lt 5 pointsize 0.0
set style line 171 lc rgb "#000000" lw 0.2 pt 9 
set style line 172 lc rgb "#000000" lw 0.2 pt 5 
set style line 173 lc rgb "#000000" lw 0.2 pt 13 
set style line 174 lc rgb "#000000" lw 0.2 pt 7 
set style line 110 lc rgb "dark-red" lw 0.2 lt 1 pt 8
set style line 210 lc rgb "red" lw 0.2 lt 1 pt 4
set style line 610 lc rgb "orange" lw 0.2 lt 1 pt 12
set style line 1110 lc rgb "dark-green" lw 0.2 lt 1 pt 6
set bar 0.3
set term postscript enhanced color
set output "out.ps"
set title "Radial Distribution Function {/Times-Italic g}({/Times-Italic r}), {/Symbol l}=1.05, {/Symbol e}=2.000"
plot "l1.05e2.000/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.05e2.000/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.05e2.000/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.05e2.000/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.05e2.000/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.05e2.000/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.05e2.000/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.05e2.000/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.05e2.000/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.05e2.000/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.05e2.000/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.05e2.000/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.05e2.000/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.05e2.000/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141
plot "l1.05e2.000/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.05e2.000/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.05e2.000/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.05e2.000/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.05e2.000/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.05e2.000/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.05e2.000/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.05e2.000/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.05e2.000/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.05e2.000/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.05e2.000/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.05e2.000/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.05e2.000/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.05e2.000/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.05e2.000/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
     "l1.05e2.000/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161
#plot "l1.02e3.331/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "l1.02e3.331/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.02e3.331/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "l1.02e3.331/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.02e3.331/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "l1.02e3.331/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.02e3.331/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "l1.02e3.331/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.02e3.331/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "l1.02e3.331/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.02e3.331/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "l1.02e3.331/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "l1.02e3.331/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "l1.02e3.331/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "l1.02e3.331/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "l1.02e3.331/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
#     "l1.02e3.331/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
#     "l1.02e3.331/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
#     "l1.02e3.331/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.02e3.331/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
#     "l1.02e3.331/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
set title "Radial Distribution Function {/Times-Italic g}({/Times-Italic r}), {/Symbol l}=1.15, {/Symbol e}=2.000"
plot "l1.15e2.000/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.15e2.000/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.15e2.000/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.15e2.000/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.15e2.000/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.15e2.000/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.15e2.000/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.15e2.000/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.15e2.000/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.15e2.000/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.15e2.000/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.15e2.000/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.15e2.000/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.15e2.000/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141
plot "l1.15e2.000/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.15e2.000/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.15e2.000/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.15e2.000/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.15e2.000/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.15e2.000/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.15e2.000/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.15e2.000/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.15e2.000/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.15e2.000/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.15e2.000/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.15e2.000/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.15e2.000/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.15e2.000/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.15e2.000/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
     "l1.15e2.000/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161
#plot "l1.05e2.650/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "l1.05e2.650/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.05e2.650/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "l1.05e2.650/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.05e2.650/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "l1.05e2.650/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.05e2.650/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "l1.05e2.650/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.05e2.650/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "l1.05e2.650/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.05e2.650/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "l1.05e2.650/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "l1.05e2.650/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "l1.05e2.650/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "l1.05e2.650/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "l1.05e2.650/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
#     "l1.05e2.650/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
#     "l1.05e2.650/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
#     "l1.05e2.650/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.05e2.650/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
#     "l1.05e2.650/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
set title "Radial Distribution Function {/Times-Italic g}({/Times-Italic r}), {/Symbol l}=1.25, {/Symbol e}=2.000"
plot "l1.25e2.000/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.25e2.000/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.25e2.000/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.25e2.000/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.25e2.000/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.25e2.000/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.25e2.000/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.25e2.000/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.25e2.000/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.25e2.000/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.25e2.000/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.25e2.000/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.25e2.000/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.25e2.000/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141
plot "l1.25e2.000/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.25e2.000/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.25e2.000/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.25e2.000/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.25e2.000/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.25e2.000/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.25e2.000/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.25e2.000/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.25e2.000/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.25e2.000/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.25e2.000/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.25e2.000/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.25e2.000/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.25e2.000/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e2.000/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
     "l1.25e2.000/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161
#plot "l1.15e1.606/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "l1.15e1.606/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.15e1.606/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "l1.15e1.606/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.15e1.606/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "l1.15e1.606/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.15e1.606/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "l1.15e1.606/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.15e1.606/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "l1.15e1.606/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.15e1.606/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "l1.15e1.606/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "l1.15e1.606/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "l1.15e1.606/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "l1.15e1.606/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "l1.15e1.606/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
#     "l1.15e1.606/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
#     "l1.15e1.606/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
#     "l1.15e1.606/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.15e1.606/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
#     "l1.15e1.606/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
plot "l1.25e1.155/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.25e1.155/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.25e1.155/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.25e1.155/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.25e1.155/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.25e1.155/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.25e1.155/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.25e1.155/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.25e1.155/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.25e1.155/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.25e1.155/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.25e1.155/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.25e1.155/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.25e1.155/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141
plot "l1.25e1.155/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.25e1.155/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.25e1.155/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.25e1.155/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.25e1.155/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.25e1.155/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
     "l1.25e1.155/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
     "l1.25e1.155/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
     "l1.25e1.155/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
     "l1.25e1.155/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.25e1.155/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
     "l1.25e1.155/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
     "l1.25e1.155/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
     "l1.25e1.155/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161, \
     "l1.25e1.155/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
     "l1.25e1.155/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 161
#plot "l1.25e1.155/vol0.01p/radial/avg.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "l1.25e1.155/vol0.01p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.25e1.155/vol0.02p/radial/avg.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "l1.25e1.155/vol0.02p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.25e1.155/vol0.03p/radial/avg.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "l1.25e1.155/vol0.03p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.25e1.155/vol0.04p/radial/avg.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "l1.25e1.155/vol0.04p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.25e1.155/vol0.05p/radial/avg.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "l1.25e1.155/vol0.05p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16 
#plot "l1.25e1.155/vol0.10p/radial/avg.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "l1.25e1.155/vol0.10p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.15p/radial/avg.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "l1.25e1.155/vol0.15p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.20p/radial/avg.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "l1.25e1.155/vol0.20p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.25p/radial/avg.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "l1.25e1.155/vol0.25p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.30p/radial/avg.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "l1.25e1.155/vol0.30p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.35p/radial/avg.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111, \
#     "l1.25e1.155/vol0.35p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.40p/radial/avg.txt" using 1:2 title "{/Symbol f} = 40%" with lines linestyle 121, \
#     "l1.25e1.155/vol0.40p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.45p/radial/avg.txt" using 1:2 title "{/Symbol f} = 45%" with lines linestyle 131, \
#     "l1.25e1.155/vol0.45p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#plot "l1.25e1.155/vol0.50p/radial/avg.txt" using 1:2 title "{/Symbol f} = 50%" with lines linestyle 141, \
#     "l1.25e1.155/vol0.50p/radial/avg.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
set title "Ratio of Radial Distribution Functions {/Times-Italic g}({/Times-Italic r_{SW}})/{/Times-Italic g}({/Times-Italic r_{HS}}) - Square-Wells over Hard Spheres"
set ylabel "{/Times-Italic g}({/Times-Italic r_{SW}})/{/Times-Italic g}({/Times-Italic r_{HS}})"
#plot [1:3][0.8:1.4]"< join saved/m10ms1kl1.05e2.650-1-35/vol0.01p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.01p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.02p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.02p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.03p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.03p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.04p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.04p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.05p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.05p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.10p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.10p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.15p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.15p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.20p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.20p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.25p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.25p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.30p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.30p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.35p/radial/avg.txt saved/m10ms1kl1.25e1.000-1-35/vol0.35p/radial/avg.txt" using 1:($2/$6) title "{/Symbol f} = 35%" with lines linestyle 111
set title "{/Times-Italic y}({/Times-Italic r})={/Times-Italic g}({/Times-Italic r_{SW}})/{/Symbol e}"
set ylabel "{/Times-Italic y}({/Times-Italic r})={/Times-Italic g}({/Times-Italic r_{SW}})/{/Symbol e}"
#plot "< join saved/m10ms1kl1.05e2.650-1-35/vol0.01p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.02p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.03p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.04p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.05p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.10p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.15p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.20p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.25p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.30p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "< join saved/m10ms1kl1.05e2.650-1-35/vol0.35p/radial/avg.txt saved/1.25sw.txt" using 1:($2/$5) title "{/Symbol f} = 35%" with lines linestyle 111
set autoscale x
set yrange [0:15]
set xrange [0:0.319072875536]
set ytics 0,2.0
set title "{/Symbol h} {/Times-Italic vs.} {/Symbol f}"
set ylabel "{/Symbol h}"
set xlabel "{/Symbol f}"
plot "l1.05e2.000/eta/etal1.05e2.000.txt" using 1:2 title "{/Symbol l} = 1.05, {/Symbol e} = 2.000" with lp linestyle 110, \
     "l1.05e2.000/eta/etal1.05e2.000.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16, \
     "l1.15e2.000/eta/etal1.15e2.000.txt" using 1:2 title "{/Symbol l} = 1.15, {/Symbol e} = 2.000" with lp linestyle 210, \
     "l1.15e2.000/eta/etal1.15e2.000.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16, \
     "l1.25e2.000/eta/etal1.25e2.000.txt" using 1:2 title "{/Symbol l} = 1.25, {/Symbol e} = 2.000" with lp linestyle 610, \
     "l1.25e2.000/eta/etal1.25e2.000.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16
#     "l1.05e2.000/eta/etal1.05e2.000.txt" using 1:5 title "bound" with lines linestyle 162, \
#     "l1.15e2.000/eta/etal1.15e2.000.txt" using 1:5 title "bound" with lines linestyle 163, \
#     "l1.25e2.000/eta/etal1.25e2.000.txt" using 1:5 title "bound" with lines linestyle 164
#     "l1.25e1.155/eta/etal1.25e1.155.txt" using 1:2 title "{/Symbol l} = 1.25, {/Symbol e} = 1.155" with lp linestyle 1110, \
#     "l1.25e1.155/eta/etal1.25e1.155.txt" using 1:2:3:4 notitle with yerrorbars linestyle 16, \
#     "l1.25e1.155/eta/etal1.25e1.155.txt" using 1:5 title "bound" with lines linestyle 165, \
#     "saved/lomakindata/l1.05e2.650.txt" using 1:2 notitle with points linestyle 171, \
#     "saved/lomakindata/l1.25e1.267.txt" using 1:2 notitle with points linestyle 172, \
#     "saved/lomakindata/l1.65e0.605.txt" using 1:2 notitle with points linestyle 173, \
#     "saved/lomakindata/l2.20e0.260.txt" using 1:2 notitle with points linestyle 174, \
#     "saved/lomakindata/adhesivespheres.txt" using 1:2 notitle with lines linestyle 161
set autoscale x
set autoscale y
set xtics auto
set ytics auto
set ylabel "total neighbors"
set xlabel "moves"
set xrange[0:100000000]
#set yrange[0:1000]
#set logscale y
set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.05, {/Symbol e}=2.000"
plot "l1.05e2.000/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.05e2.000/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.05e2.000/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.05e2.000/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.05e2.000/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.05e2.000/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 101, \
     "l1.05e2.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 101, \
     "l1.05e2.000/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 121, \
     "l1.05e2.000/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 121, \
     "l1.05e2.000/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.05e2.000/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.15, {/Symbol e}=2.000"
plot "l1.15e2.000/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.15e2.000/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.15e2.000/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.15e2.000/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.15e2.000/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.15e2.000/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 101, \
     "l1.15e2.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 101, \
     "l1.15e2.000/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 121, \
     "l1.15e2.000/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 121, \
     "l1.15e2.000/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.15e2.000/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.25, {/Symbol e}=2.000"
plot "l1.25e2.000/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.25e2.000/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.25e2.000/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.25e2.000/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.25e2.000/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.25e2.000/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 101, \
     "l1.25e2.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 101, \
     "l1.25e2.000/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 121, \
     "l1.25e2.000/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 121, \
     "l1.25e2.000/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.25e2.000/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
set autoscale x
set autoscale y
set xtics auto
set ytics auto
set ylabel "total neighbors"
set xlabel "moves"
set xrange[0:2000000]
#set yrange[0:1000]
#set logscale y
set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.05, {/Symbol e}=2.000"
plot "l1.05e2.000/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.05e2.000/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.05e2.000/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.05e2.000/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.05e2.000/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.05e2.000/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 101, \
     "l1.05e2.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 101, \
     "l1.05e2.000/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 121, \
     "l1.05e2.000/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 121, \
     "l1.05e2.000/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.05e2.000/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.15, {/Symbol e}=2.000"
plot "l1.15e2.000/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.15e2.000/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.15e2.000/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.15e2.000/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.15e2.000/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.15e2.000/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 101, \
     "l1.15e2.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 101, \
     "l1.15e2.000/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 121, \
     "l1.15e2.000/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 121, \
     "l1.15e2.000/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.15e2.000/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.25, {/Symbol e}=2.000"
plot "l1.25e2.000/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
     "l1.25e2.000/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
     "l1.25e2.000/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
     "l1.25e2.000/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
     "l1.25e2.000/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
     "l1.25e2.000/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 101, \
     "l1.25e2.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 101, \
     "l1.25e2.000/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 121, \
     "l1.25e2.000/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 121, \
     "l1.25e2.000/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
     "l1.25e2.000/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
#set title "Total Number of Neighbors vs. Moves {/Symbol l}=1.25, {/Symbol e}=1.155"
#plot "l1.25e1.155/vol0.01p/neighbors.txt" using 1:2 title "{/Symbol f} = 1%" with lines linestyle 11, \
#     "l1.25e1.155/vol0.02p/neighbors.txt" using 1:2 title "{/Symbol f} = 2%" with lines linestyle 21, \
#     "l1.25e1.155/vol0.03p/neighbors.txt" using 1:2 title "{/Symbol f} = 3%" with lines linestyle 31, \
#     "l1.25e1.155/vol0.04p/neighbors.txt" using 1:2 title "{/Symbol f} = 4%" with lines linestyle 41, \
#     "l1.25e1.155/vol0.05p/neighbors.txt" using 1:2 title "{/Symbol f} = 5%" with lines linestyle 51, \
#     "l1.25e1.155/vol0.10p/neighbors.txt" using 1:2 title "{/Symbol f} = 10%" with lines linestyle 61, \
#     "l1.25e1.155/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%" with lines linestyle 71, \
#     "l1.25e1.155/vol0.20p/neighbors.txt" using 1:2 title "{/Symbol f} = 20%" with lines linestyle 81, \
#     "l1.25e1.155/vol0.25p/neighbors.txt" using 1:2 title "{/Symbol f} = 25%" with lines linestyle 91, \
#     "l1.25e1.155/vol0.30p/neighbors.txt" using 1:2 title "{/Symbol f} = 30%" with lines linestyle 101, \
#     "l1.25e1.155/vol0.35p/neighbors.txt" using 1:2 title "{/Symbol f} = 35%" with lines linestyle 111
set title "Total Number of Neighbors vs. Moves {/Symbol f} = 0.2%, {/Symbol l} = 1.05, {/Symbol e} = 2.650"
set xrange[0:100000000]
plot "l1.05e2.650/vol0.02p/neighbors.txt" using 1:2 title "Total Neighbors" with lines linestyle 11, \
     "l1.05e2.650/vol0.02p/neighbors.txt" using 1:3 title "Neighbors In Square Well Only" with lines linestyle 21, \
     "l1.05e2.650/vol0.02p/neighbors.txt" using 1:4 title "Neighbors In Patch Only" with lines linestyle 31
#plot "l1.05e2.200/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.200" with lines linestyle 11, \
#     "l1.05e2.300/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.300" with lines linestyle 21, \
#     "l1.05e2.400/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.400" with lines linestyle 31, \
#     "l1.05e2.500/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.500" with lines linestyle 41, \
#     "l1.05e2.600/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.600" with lines linestyle 51, \
#     "l1.05e2.700/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.700" with lines linestyle 61, \
#     "l1.05e2.800/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.800" with lines linestyle 71, \
#     "l1.05e2.900/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 2.900" with lines linestyle 81, \
#     "l1.05e3.000/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 3.000" with lines linestyle 91, \
#     "l1.05e3.100/vol0.15p/neighbors.txt" using 1:2 title "{/Symbol f} = 15%, {/Symbol l} = 1.05, {/Symbol e} = 3.100" with lines linestyle 101
