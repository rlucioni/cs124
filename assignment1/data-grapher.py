import matplotlib.pyplot as plt
from pylab import *

plt.clf()

### NUMBER OF VERTICES ###
# xs and ys  must have the same dimension
#xs = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]
xs = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]

### AVERAGE MST SIZE ###

# dimension 0
ys = [0.184663, 0.186921, 0.075035, 0.048077, 0.020567, 0.012300, 0.006896, 0.004003, 0.002163, 0.001320]

# dimension 2
#ys = [0.319794, 0.281464, 0.185328, 0.135068, 0.106834, 0.079031, 0.057961, 0.040060, 0.032302, 0.020767]

# dimension 3
#ys = [0.503107, 0.359172, 0.316882, 0.246209, 0.206330, 0.214786, 0.136989, 0.124195, 0.090718, 0.070720]

# dimension 4
#ys = [0.714366, 0.523572, 0.439403, 0.400802, 0.348604, 0.282274, 0.265582, 0.239024, 0.185937, 0.138841]

p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

### DIMENSION 0
#plt.title('Average MST Size Over 5 Trials, Dimension = 0')
plt.title('Heaviest MST Edge Over 5 Trials, Dimension = 0')
plt.xlabel('Vertices')
#plt.ylabel('MST Size')
plt.ylabel('Heaviest MST Edge')
plt.axis([0,8500,0.0,0.2])
#plt.legend((p1,), ('MST Size',), 'upper right')

# save figure as a pdf
savefig('kruskals-dimension-0.pdf')

### DIMENSION 2

### DIMENSION 3

### DIMENSION 4
