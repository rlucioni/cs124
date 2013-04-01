import matplotlib.pyplot as plt
import sys
from pylab import *

plt.clf()

# xs and ys must have the same dimension!!
if len(sys.argv) != 6:
    print 'usage : ' + __file__ + ' x-min x-max x-interval data-file iters-per-x'
    sys.exit(1)

try:
    inputFile = open(sys.argv[4], 'r')
except Exception:
    print "This file does not exist or cannot be found/read from"
    sys.exit(1)

### X Axis ###
xmin = int(sys.argv[1])
xmax = int(sys.argv[2])
xint = int(sys.argv[3])
xs = range(xmin, xmax, xint)

### Y Axis ###
iters_per_x = int(sys.argv[5])
ymin = None
ymax = None
ys = []
runner = 0
num_iters = 0
for line in inputFile:
    runner += int(line)
    num_iters += 1
    if num_iters == iters_per_x:
        avg = runner / iters_per_x
        num_iters = 0
        if ymin is None or avg < ymin:
            ymin = avg
        if ymax is None or avg > ymax:
            ymax = avg
            ys.append(avg)
inputFile.close

p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

plt.title('Crossover vs. Time to Compute AB = C, n = 500') # note that this is for 012 matrices
#plt.title('Crossover vs. Time to Compute AB = C, n = 1000') # note that this is for 012 matrices
#plt.title('Crossover vs. Time to Compute AB = C, n = 2500') # note that this is for 012 matrices

plt.xlabel('Crossover')
plt.ylabel('Compute Time (seconds)')
plt.axis([xmin,xmax,ymin,ymax])

# save figure as a pdf
savefig('POOP-crossover-v-compute-time-500.pdf')
#savefig('cutoff-v-compute-time-1000.pdf')
#savefig('cutoff-v-compute-time-2500.pdf')
