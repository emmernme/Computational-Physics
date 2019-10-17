"""
Program to make plot for the report
"""

import matplotlib.pyplot as plt
import numpy as np
from math import sqrt, exp

#Initializing constants and linspace for distance between the electrons
n = 100
alpha = 2


r1 = np.linspace(0,3,n)
r2 = np.linspace(-3,0,n)

#Finds positive
def wave_p(r):
    return exp(-2*alpha*(r))

def wave_n(r):
    return exp(2*alpha*(r))

P1 = np.zeros(n)
P2 = np.zeros(n)

for i in range(n):
    P1[i] = wave_p(r1[i])
    P2[i] = wave_n(r2[i])


plt.plot(r1, P1, color = 'b')
plt.plot(r2, P2, color = 'b')
plt.xlabel('r')
plt.ylabel('Wave function')
plt.show()
