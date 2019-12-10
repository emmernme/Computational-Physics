import matplotlib.pyplot as plt
import numpy as np



infile = open("energy.dat", 'r')

x = []
y = []

for i in infile.readlines():
    line = i.split()
    x.append(float(line[0]))
    #y.append(float(line[1]))

x = np.array(x)
y = np.array(y)
t = np.linspace(0,5,len(x))


plt.plot(t, x)
#plt.axhline(1.18315e+26, color='r')
plt.show()


#plt.savefig("./Latex/Plot/xy_vs_time.png", dpi=300)