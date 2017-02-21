set term png
set out "lotka-volterra.png"
set style data line

set xla "t"
set yla "x"
p "lv_euler.dat" t "Euler"\
, "lv_rk.dat" t "Runge-Kutta"

set out "lotka-volterra-h.png"

set xla "t"
set yla "H"
p [][0:] "lv_euler.dat" u 1:4 t "Euler"\
, "lv_rk.dat" u 1:4 t "Runge-Kutta"

set out "harmonic-oscillator.png"

set xla "x"
set xla "y"

p "ho_euler.dat" u 2:3 t "Euler"\
, "ho_rk.dat" u 2:3 t "Runge-Kutta"

set out "harmonic-oscillator-h.png"

set xla "t"
set yla "H"
p [][0:] "ho_euler.dat" u 1:4 t "Euler"\
, "ho_rk.dat" u 1:4 t "Runge-Kutta"

