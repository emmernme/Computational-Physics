"""
Plotting a histogram of the energies calculated in the MC loop
"""

import matplotlib.pyplot as plt
import numpy as np


"""
For
"""
first = open('E_count.dat', 'r')

count = []
energy = []

data = first.readlines()

for i in range(len(data)):
    line = data[i]
    energy.append(float(line))

#M = np.array(M)



plt.hist(energy, 116, density = 1)
#plt.plot(x1, M, label='Magnetization')
plt.axvline(400*(-1.23328)+np.sqrt(7.64854)*20, linestyle= 'dashed', color = 'r')
plt.axvline(400*(-1.23874)-np.sqrt(7.64854)*20, linestyle= 'dashed', color = 'r')
plt.title('Hits for random initial spin and T=1')
plt.xlabel('Energy')
plt.ylabel('Probability')
plt.show()
