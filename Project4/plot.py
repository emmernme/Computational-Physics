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
plt.axvline(-1.23328*400, linestyle= 'dashed', color = 'r', label = 'Mean energy')
plt.legend()
#plt.axvline(x=-1.23874*400-7.64854, linestyle= 'dashed', color = 'r')
plt.title('Hits for random initial spin and T=1')
plt.xlabel('Energy')
plt.ylabel('Probability')
plt.show()
