set terminal pdfcairo color size 10in,8in
set title "Avg Jobs in Parking Lot - 100"
#set key top left Left reverse
set key off
set xlabel "1/Job Rate = lambda (minutes)"
set ylabel "Job Processing Time (minutes)"
set zlabel "Avg Jobs in Parking Lot"
#set xr [1.5:8.5]
#set yr [0:5000]
#set dgrid3d 30, 30 
set view 85, 30
set ticslevel 0
set datafile separator "	"
set output "SurfaceAvgJobsInParkingLot_LowBW_100.pdf"
splot for [i=0:22] "SurfaceA.txt" index i u 4:5:19 lt rgb "red" with lines,  \
      for [j=0:9] "SurfaceB.txt" index j u 4:5:19 lt rgb "red" with lines