import matplotlib.pyplot as plt
import numpy as np


"""
For
"""
infile = open('phase_transitions.dat', 'r')
infile.readline()
infile.readline()
infile.readline()

E_mean = np.zeros((4,40))
M_mean = np.zeros((4,40))
specific_heat = np.zeros((4,40))
suceptibility = np.zeros((4,40))


for k in range(40):
    for i in range(4):
        data = infile.readline()
        line = data.split()
        E_mean[i,k] = line[2]
        M_mean[i,k] = line[3]
        specific_heat[i,k] = line[4]
        suceptibility[i,k] = line[5]
    infile.readline()
    infile.readline()

T = np.linspace(2, 10, 40)


plt.plot(T, E_mean[0], label='L=40')
plt.plot(T, E_mean[1], label='L=60')
plt.plot(T, E_mean[2], label='L=80')
plt.plot(T, E_mean[3], label='L=100')
plt.title('Mean energy')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Energy')
plt.show()

plt.plot(T, M_mean[0],label='L=40')
plt.plot(T, M_mean[1],label='L=60')
plt.plot(T, M_mean[2],label='L=80')
plt.plot(T, M_mean[3],label='L=100')
plt.title('Mean magnetization')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('magnetization')
plt.show()

plt.plot(T, specific_heat[0], label='L=40')
plt.plot(T, specific_heat[1], label='L=60')
plt.plot(T, specific_heat[2], label='L=80')
plt.plot(T, specific_heat[3], label='L=100')
plt.title(r'Specific Heat ($C_v$)')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Specific heat')
plt.show()

plt.plot(T, suceptibility[0], label='L=40')
plt.plot(T, suceptibility[1], label='L=60')
plt.plot(T, suceptibility[2], label='L=80')
plt.plot(T, suceptibility[3], label='L=100')
plt.title('Susceptibility')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Susceptibility')
plt.show()
