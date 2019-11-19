"""
Plotting the results from the phase transition run (phase_transitions_mpi.cpp)
"""
import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy import interpolate

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

T = np.linspace(2.0, 2.8, T_steps)


"""
Interpolation for specific heat and susceptibility
"""
s_1  = interpolate.interp1d(T, specific_heat[0])
s_2  = interpolate.interp1d(T, specific_heat[1])
s_3  = interpolate.interp1d(T, specific_heat[2])
s_4  = interpolate.interp1d(T, specific_heat[3])

xi_1 = interpolate.interp1d(T, susceptibility[0])
xi_2 = interpolate.interp1d(T, susceptibility[1])
xi_3 = interpolate.interp1d(T, susceptibility[2])
xi_4 = interpolate.interp1d(T, susceptibility[3])


T_new = np.linspace(2.0, 2.8, T_steps-1)

specific_heat_40  = s_1(T_new)
specific_heat_60  = s_2(T_new)
specific_heat_80  = s_3(T_new)
specific_heat_100 = s_4(T_new)

susceptibility_40  = xi_1(T_new)
susceptibility_60  = xi_2(T_new)
susceptibility_80  = xi_3(T_new)
susceptibility_100 = xi_4(T_new)

"""
Finding the maximum temperature, known as critical temperature
"""
Tpos1_40 = np.argmax(specific_heat_40)
Tpos1_60 = np.argmax(specific_heat_60)
Tpos1_80 = np.argmax(specific_heat_80)
Tpos1_100 = np.argmax(specific_heat_100)

Tval1_40 = T_new[Tpos1_40]
Tval1_60 = T_new[Tpos1_60]
Tval1_80 = T_new[Tpos1_80]
Tval1_100 = T_new[Tpos1_100]

Tpos2_40 = np.argmax(susceptibility_40)
Tpos2_60 = np.argmax(susceptibility_60)
Tpos2_80 = np.argmax(susceptibility_80)
Tpos2_100 = np.argmax(susceptibility_100)

Tval2_40 = T_new[Tpos2_40]
Tval2_60 = T_new[Tpos2_60]
Tval2_80 = T_new[Tpos2_80]
Tval2_100 = T_new[Tpos2_100]


print("Max specific heat for L =  40 at T=", Tval1_40)
print("Max specific heat for L =  60 at T=", Tval1_60)
print("Max specific heat for L =  80 at T=", Tval1_80)
print("Max specific heat for L = 100 at T=", Tval1_100,"\n")
print("Max susceptibility for L =  40 at T=", Tval2_40)
print("Max susceptibility for L =  60 at T=", Tval2_60)
print("Max susceptibility for L =  80 at T=", Tval2_80)
print("Max susceptibility for L = 100 at T=", Tval2_100)


"""
Plotting
"""

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

plt.plot(T_new, specific_heat_40, label='L=40')
plt.plot(T_new, specific_heat_60, label='L=60')
plt.plot(T_new, specific_heat_80, label='L=80')
plt.plot(T_new, specific_heat_100, label='L=100')
plt.title(r'Specific Heat ($C_v$)')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Specific heat')
plt.savefig("Specific_heat.png", dpi=300)
plt.show()

plt.plot(T_new, susceptibility_40, label='L=40')
plt.plot(T_new, susceptibility_60, label='L=60')
plt.plot(T_new, susceptibility_80, label='L=80')
plt.plot(T_new, susceptibility_100, label='L=100')
plt.title('Susceptibility')
plt.legend()
plt.xlabel('Temperature')
plt.ylabel('Susceptibility')
plt.savefig("Susceptibility.png", dpi=300)
plt.show()
