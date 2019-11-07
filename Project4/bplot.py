import matplotlib.pyplot as pl
import numpy as np


"""
For
"""
first = open('n_10.dat', 'r')


data = first.readline()
tot1 = data.split(',')
x1 = np.linspace(0,1, len(tot1)-1)
del tot1[-1]

for i in range(len(tot1)):
    tot1[i] = float(tot1[i])


"""
For n = 100
"""
second = open('n_100.dat', 'r')
data3 = second.readline()
tot3 = data3.split(',')
x3 = np.linspace(0,1, len(tot3)-1)
del tot3[-1]

for i in range(len(tot3)):
    tot3[i] = float(tot3[i])

"""
For n = n_1000
"""
third = open('n_1000.dat', 'r')
data4 = third.readline()
tot4 = data4.split(',')
x4 = np.linspace(0,1, len(tot4)-1)
del tot4[-1]

for i in range(len(tot4)):
    tot4[i] = float(tot4[i])


"""
Plot
"""


plt.stem(x, y, use_line_collection=True)
plt.xaxis('E')
plt.yaxis('# hits')
