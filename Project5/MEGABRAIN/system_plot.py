import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D



infile = open("system.data", 'r')

infile.readline()
info = infile.readline()
info = info.split(',')

n = int(info[1])
system = int(info[-1])

earth = np.zeros((n, 3))
sun = np.zeros((n,3))

infile.readline()
infile.readline()
infile.readline()
infile.readline()

for i in range(n-1):
    line1 = infile.readline()
    line1 = line1.split('=')
    element1 = line1[1].split(',')
    sun[i,0] = float(element1[0])
    sun[i,1] = float(element1[1])
    sun[i,2] = float(element1[2])

    line2 = infile.readline()
    line2 = line2.split('=')
    element2 = line2[1].split(',')
    earth[i,0] = float(element2[0])
    earth[i,1] = float(element2[1])
    earth[i,2] = float(element2[2])


fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

x1 = sun[0]
y1 = sun[1]
z1 = sun[2]

x2 = earth[0]
y2 = earth[1]
z2 = earth[2]

ax.plot(x1, y1, z1)
ax.plot(x2, y2, z2)

plt.show()
