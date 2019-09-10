import matplotlib.pyplot as plt
import numpy as np

"""
For n = 10
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
Analytical solution
"""


exact = open("n_1000.dat", "r")
exact.readline()

data2 = exact.readline()
tot2 = data2.split(',')
x2 = np.linspace(0,1,len(tot2)-1)
del tot2[-1]



for i in range(len(tot2)):
    tot2[i] = float(tot2[i])


"""
Plot
"""

plt.plot(x1, tot1, label = 'n = 10')
plt.plot(x3, tot3, label = 'n = 100')
plt.plot(x4, tot4, label = 'n = 1000')
plt.plot(x2, tot2, linestyle = ':', label = 'Analytical')
plt.legend()
plt.show()
