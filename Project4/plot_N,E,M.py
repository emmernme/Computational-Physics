import matplotlib.pyplot as plt
import numpy as np
import sys


"""
For
"""
filename = sys.argv[1]
file = open(filename, 'r')

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
plt.title('Stabilisation of energy')
plt.xlabel('MC cycles')
plt.legend()
plt.savefig("E_"+ filename +".png", dpi=300)
plt.show()

plt.plot(N, M, label=labels[2])
plt.title('Stabilisation of magnetisation')
plt.savefig("M_"+ filename +".png", dpi=300)
plt.show()
