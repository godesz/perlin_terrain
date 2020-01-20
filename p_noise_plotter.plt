# GNUPlotban els�nek be kell tall�zni a mapp�t
#  cd 'D:\Dokumentumok\ts\utravalo\p_noise'
# majd ut�na ezt a f�jlt megh�vni, �gy:
# load "p_noise_plotter.plt" 
# megjelenik a k�perny�n �S egy PNG-be lementve is
# ezt nevezz�tek �t mert fel�l�rja a k�vetkez�

xr = 800
yr = 800
filename = sprintf("perlinke_%s.png",strftime("%H_%M_%S_%d_%b_%Y",time(0.0)))
#strftime("%H_%M_%.3S_%d_%b_%Y",time(0.0))

set palette rgb  30,30,30
#10,13,16
#18,19,20
set xrange [0:xr]
set yrange [0:yr]

unset colorbox
se te wi
se g 

unset border
unset xtics
unset ytics
plot 'perlin_out.txt' using 1:2:3 w image not


set terminal png size xr, yr
set output filename
plot 'perlin_out.txt' using 1:2:3 w image not

set colorbox
