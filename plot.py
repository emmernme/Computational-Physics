
import matplotlib.pyplot as plt
import numpy as np
from math import sqrt, exp


n = 100
alpha = 2

x = np.linspace(0,0.45, n)
y = np.linspace(0,0.45, n)
z = np.linspace(0,0.45, n)


r1 = np.zeros(n)
r2 = np.zeros(n)


for i in range(n):
    r2[i] = sqrt(x[i]**2 + y[i]**2 + z[i]**2)


def wave(r1,r2):
    return exp(-2*alpha*(r1+r2))

P = np.zeros(n)
for i in range(n):
    P[i] = wave(r1[i], r2[i])


plt.plot(r2,P)
plt.show()
