import matplotlib.pyplot as plt
import numpy as np



infile = open("euler.dat", 'r')

x = []
y = []

for i in infile.readlines():
    line = i.split()
    x.append(float(line[0]))
    y.append(float(line[1]))


plt.plot(x,y)
plt.show()
