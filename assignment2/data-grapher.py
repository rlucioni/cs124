import matplotlib.pyplot as plt
from pylab import *

plt.clf()

# xs and ys  must have the same dimension!!

### CUTOFF ###
xs = []

### TIME TO COMPUTE ###
# dimension 1000
ys = []

# dimension 16000
#ys = []

p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

plt.title('Cutoff vs. Time to Compute AB = C, Dimension = 1000')
#plt.title('Cutoff vs. Time to Compute AB = C, Dimension = 16000')
plt.xlabel('Cutoff')
plt.ylabel('Compute Time (seconds)')
plt.axis([0,10000,0.0,1.5])
#plt.axis([0,10000,0.0,10.0])
#plt.legend((p1,), ('MST Size',), 'upper right')

# save figure as a pdf
savefig('plot-dimension-1000.pdf')
#savefig('plot-dimension-16000.pdf')