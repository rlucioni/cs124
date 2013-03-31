import matplotlib.pyplot as plt
from pylab import *

plt.clf()

# xs and ys  must have the same dimension!!

### CUTOFF ###
xs = range(1,101)

### TIME TO COMPUTE ###
# dimension 500
ys = []

# dimension 1000
zs = []

# dimension 2500
qs = []

p1, = plt.plot(xs, ys, color='r')
p2, = plt.plot(xs, zs, color='g')
p3, = plt.plot(xs, qs, color='b')

plt.grid(b=1)

plt.title('Cutoff vs. Time to Compute AB = C') # note that this is for 012 matrices
plt.xlabel('Cutoff')
plt.ylabel('Compute Time (seconds)')
plt.axis([0,200,0.1,0.25])
plt.legend((p1,p2,p3), ('n = 500','n = 1000','n = 2500'), 'lower right')

# save figure as a pdf
savefig('cutoff-v-compute-time.pdf')
