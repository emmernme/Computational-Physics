import matplotlib.pyplot as plt
import numpy as np

# This import registers the 3D projection, but is otherwise unused.
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import


infile = open("system.dat", 'r')

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


x_sun = np.zeros((n-1,1))
y_sun = np.zeros((n-1,1))
z_sun = np.zeros((n-1,1))

x_earth = np.zeros((n-1,1))
y_earth = np.zeros((n-1,1))
z_earth = np.zeros((n-1,1))

for i in range(len(earth)-1):
    x_sun[i] = sun[i,0]
    y_sun[i] = sun[i,1]
    z_sun[i] = sun[i,2]

    x_earth[i] = earth[i,0]
    y_earth[i] = earth[i,1]
    z_earth[i] = earth[i,2]

fig = plt.figure()
ax = fig.gca(projection='3d')


ax.plot(x_earth.flatten(), y_earth.flatten(), z_earth.flatten(), label='Earth')
ax.plot(x_sun.flatten(), y_sun.flatten(), z_sun.flatten(), label='Sun', color="#ccff00", linewidth=10)
ax.legend()
ax.set_xlabel("Xpos")
ax.set_ylabel("Ypos")
plt.show()
#plt.savefig('fig1.png')
