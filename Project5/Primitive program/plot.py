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
plt.title(r'Energy $(E_0 - E_t)$')
plt.xlabel('Time [years]')
plt.ylabel('Difference in energy [J]')
plt.savefig("./Latex/Plot/energy.png", dpi=300)