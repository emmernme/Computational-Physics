"""
Plotting the results from the phase transition run (phase_transitions_mpi.cpp)
"""
import sys
import matplotlib.pyplot as plt
import numpy as np


"""
For
"""
infile = open(sys.argv[1], 'r')
infile.readline()
infile.readline()
infile.readline()
T_steps = 20

E_mean = np.zeros((4,T_steps))
M_mean = np.zeros((4,T_steps))
specific_heat = np.zeros((4,T_steps))
susceptibility = np.zeros((4,T_steps))


for k in range(T_steps):
    for i in range(4):
        data = infile.readline()
        line = data.split()
        E_mean[i,k] = line[2]
        M_mean[i,k] = line[3]
        specific_heat[i,k] = line[4]
        susceptibility[i,k] = line[5]
    infile.readline()
    infile.readline()

T = np.linspace(2, 2.8, T_steps)

plt.plot(T, E_mean[0], label='L=40')
plt.plot(T, E_mean[1], label='L=60')
plt.plot(T, E_mean[2], label='L=80')
plt.plot(T, E_mean[3], label='L=100')
plt.title('Mean energy')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Energy')
plt.savefig("Mean_E.png", dpi=300)
plt.show()

plt.plot(T, M_mean[0],label='L=40')
plt.plot(T, M_mean[1],label='L=60')
plt.plot(T, M_mean[2],label='L=80')
plt.plot(T, M_mean[3],label='L=100')
plt.title('Mean magnetization')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('magnetization')
plt.savefig("Mean_M.png", dpi=300)
plt.show()

plt.plot(T, specific_heat[0], label='L=40')
plt.plot(T, specific_heat[1], label='L=60')
plt.plot(T, specific_heat[2], label='L=80')
plt.plot(T, specific_heat[3], label='L=100')
plt.title(r'Specific Heat ($C_v$)')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Specific heat')
plt.savefig("Specific_heat.png", dpi=300)
plt.show()

plt.plot(T, susceptibility[0], label='L=40')
plt.plot(T, susceptibility[1], label='L=60')
plt.plot(T, susceptibility[2], label='L=80')
plt.plot(T, susceptibility[3], label='L=100')
plt.title('Susceptibility')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Susceptibility')
plt.savefig("Susceptibility.png", dpi=300)
plt.show()
