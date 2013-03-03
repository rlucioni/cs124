import matplotlib.pyplot as plt
from pylab import *

plt.clf()

### NUMBER OF VERTICES ###
# xs and ys  must have the same dimension
xs = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]

### AVERAGE MST SIZE ###

# dimension 0
#ys = [0.929531, 0.967641, 1.137753, 1.185701, 1.173584, 1.178243, 1.192734, 1.209832, 1.204681, 1.198778, 1.203032, 1.202110]

# dimension 2
#ys = [2.818149, 3.872131, 5.475579, 7.691335, 10.648638, 14.866658, 20.792080, 29.512669, 41.692554 , 58.925728 , 83.156471 , 117.546494]

# dimension 3
#ys = [4.566855, 6.925250, 11.133249 , 17.818338 , 27.646692 , 43.728298 , 68.244339 , 107.170555, 168.915375, 266.453552, 422.085632, 667.827393]

# dimension 4
ys = [6.159772, 10.294616, 17.242434, 28.670132, 47.566528, 78.802025, 129.762085 , 217.340424 , 361.436401 , 602.498047 , 1007.845337, 1688.796265]

p1, = plt.plot(xs, ys, color='b')

plt.grid(b=1)

### DIMENSION 0
plt.title('Average MST Size Over 5 Trials, Dimension = 4')
plt.xlabel('Vertices')
plt.ylabel('MST Size')
plt.axis([0,33000,0.0,1690.0])
#plt.legend((p1,), ('MST Size',), 'upper right')

# save figure as a pdf
savefig('kruskals-dimension-4.pdf')

### DIMENSION 2

### DIMENSION 3

### DIMENSION 4
