import matplotlib.pyplot as plt
import numpy as np


infile = open('n_1000.dat', 'r')


data = infile.readline()
tot1 = data.split(',')
x = np.linspace(0,1, len(tot1)-1)
del tot1[-1]



data2 = infile.readline()
tot2 = data2.split(',')

for i in range(len(tot1)):
    tot1[i] = float(tot1[i])
    tot2[i] = float(tot2[i])

del tot2[-1]
print(tot1, tot2)
#plt.plot(x, tot1, label = 'Computed')
plt.plot(x, tot2, label = 'Exact')
#plt.plot(x3, y3, label = 'n = 1000')
plt.legend()
plt.show()
