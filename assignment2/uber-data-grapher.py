import matplotlib.pyplot as plt
import sys
from pylab import *

plt.clf()

# xs and ys must have the same dimension!!
if len(sys.argv) != 5:
    print 'usage : ' + __file__ + ' x-min x-max x-interval data-file'
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
i = 1
ymini = 1
ymin = None
ymax = None
ys = []
for line in inputFile:
    line = line.strip()
    i = i + 1
    y = float(line)
    if ymin is None or y < ymin:
        ymin = y
        ymini = i
    if ymax is None or y > ymax:
        ymax = y
    ys.append(y)
inputFile.close

p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

plt.title('Crossover vs. Time to Compute AB = C, n = 500') # note that this is for 012 matrices

plt.xlabel('Crossover')
plt.ylabel('Compute Time (seconds)')
plt.axis([xmin,xmax,ymin,ymax])
print ymin
print ymini

# save figure as a pdf
savefig('uber-crossover-v-compute-time-500.pdf')
