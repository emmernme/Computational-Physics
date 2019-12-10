import matplotlib.pyplot as plt
import numpy as np



infile = open("verlet.dat", 'r')

x = []
y = []

for i in infile.readlines():
    line = i.split()
    x.append(float(line[0]))
    y.append(float(line[1]))

x = np.array(x)
y = np.array(y)
t = np.linspace(0,5,len(x))


plt.plot(t, x, label='x position')
plt.plot(t, y, label='y position')
plt.title('Decomposed position')
plt.xlabel('Time (years)')
plt.ylabel('Distance (AU)')
plt.legend()
plt.savefig("./Latex/Plot/xy_vs_time.png", dpi=300)