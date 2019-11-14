import matplotlib.pyplot as plt
import numpy as np


"""
For
"""
first = open('E_mean-M_mean.dat', 'r')
first.readline()

E = []
M = []

<<<<<<< HEAD
for i in range(1*10**6 - 1):
    line = first.readline()
    element = line.split(',')
    E.append(abs(float(element[0])))
    M.append(float(element[1]))
=======
for i in first.readlines():
    line = i.split(',')
    E.append(abs(float(line[0])))
    M.append(float(line[1]))
>>>>>>> 4a67580669de241548cb98c3a69f1375ea5417a0

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
