set terminal pdfcairo color size 5in,3.5in
#set title "Avg Jobs in Parking Lot - 250"
#set key top left Left reverse
set key off
set xlabel "{/Symbol l} = 1/Job Rate (minutes)" offset 0, -2 
set ylabel "Job Processing Time (minutes)" offset -4, -2.5
set zlabel "Avg Jobs in Parking Lot" offset -1, 0 rotate by 90
set tmargin at screen 0.95
set bmargin at screen 0.2
set rmargin at screen 0.8
set lmargin at screen 0.22
#set xr [1.5:8.5]
#set yr [0:5000]
#set dgrid3d 30, 30  
set zr [0:1600]
set xtics offset 0,-1
set ytics offset 3, -.5
set view 85, 30
set ticslevel 0
set datafile separator "	"
set output "SurfaceAvgJobsInParkingLot_LowBW_250.pdf"
splot for [i=18:26]   "SurfaceA.txt" index i u 5:6:20 lt rgb "gray60" with lines,  \
      for [j=58:86] "SurfaceB.txt" index j u 5:6:20 lt rgb "gray60" with lines