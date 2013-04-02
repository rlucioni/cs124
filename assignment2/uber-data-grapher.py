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
xs = range(xmin, xmax + 1, xint)

### Y Axis ###
i = 1
ymin, ymini = None, 1
ymax, ymaxi = None, 1
ys = []
for line in inputFile:
    line = line.strip()
    try:
        float(line)
        y = float(line)
        if ymin is None or y < ymin:
            ymin, ymini = y, i
        if ymax is None or y > ymax:
            ymax, ymaxi = y, i
        ys.append(y)
    except ValueError:
        print "Could Not Convert \"%s\" to float" % line
    i += 1
inputFile.close

p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

plt.title('Crossover vs. Time to Compute AB = C, n = 500') # note that this is for 012 matrices

plt.xlabel('Crossover')
plt.ylabel('Compute Time (seconds)')
plt.axis([xmin,xmax,ymin,125])
print "MIN: (%d, %.2f)" % (ymini, ymin)
print "MAX: (%d, %.2f)" % (ymaxi, ymax)

# save figure as a pdf
savefig('uber-crossover-v-compute-time-500.pdf')
