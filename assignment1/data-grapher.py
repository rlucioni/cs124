import matplotlib.pyplot as plt
from pylab import *

plt.clf()

### NUMBER OF VERTICES ###
# xs and ys  must have the same dimension
xs = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]


### AVERAGE MST SIZE ###

# dimension 0
ys = range(0,12)

# dimension 2

# dimension 3

# dimension 4


p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

### DIMENSION 0
plt.title('Average MST Size Over 5 Trials, Dimension = 0')
plt.xlabel('Vertices')
plt.ylabel('MST Size')
plt.axis([0,35000,0.00,12])
#plt.legend((p1,), ('MST Size',), 'upper right')

# save figure as a pdf
savefig('kruskals-dimension-0.pdf')

### DIMENSION 2

### DIMENSION 3

### DIMENSION 4
