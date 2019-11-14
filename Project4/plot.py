import matplotlib.pyplot as plt
import numpy as np


"""
For
"""
first = open('E_mean-M_mean.dat', 'r')
first.readline()

E = []
M = []

for i in first.readlines():
    line = i.split(',')
    E.append(abs(float(line[0])))
    M.append(float(line[1]))

E = np.array(E)
M = np.array(M)

x1 = np.linspace(0,len(E), len(E))

print(E[0], '  ', E[-1])
print(M[0], '  ', M[-1])


plt.plot(x1, E, label='Energy')
plt.plot(x1, M, label='Magnetization')
plt.legend()
plt.xlabel('# MC cycles')
plt.show()