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



plt.hist(energy,8, density = True)
#plt.plot(x1, M, label='Magnetization')
plt.title('Hits for random initial spin and T=2.4')
plt.xlabel('Energy')
plt.ylabel('Counts')
plt.show()
