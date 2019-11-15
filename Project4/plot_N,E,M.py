import matplotlib.pyplot as plt
import numpy as np


"""
For
"""

file = open('MC_cycles_mean_E+M_T=1.dat', 'r')

labels = file.readline()
labels = labels.split(",")
data = file.readlines()

N = []
E = []
M = []

for i in range(len(data)):
    line = data[i].split(",")
    N.append((float(line[0])))
    E.append((float(line[1])))
    M.append((float(line[2])))


plt.plot(N, E, label=labels[1])
#plt.plot(N, M, label=labels[2])
plt.title('Stabilisation of energy and magnetisation')
plt.xlabel('MC cycles')
plt.legend()
plt.show()