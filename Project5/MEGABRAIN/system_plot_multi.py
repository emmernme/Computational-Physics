import matplotlib.pyplot as plt
import numpy as np
import sys
from mpl_toolkits.mplot3d import Axes3D

file_count = len(sys.argv) - 1
files = []
for i in range(file_count):
    files.append(sys.argv[i+1])

systems = []
for file in files:
    infile = open(file, 'r')
    infile.readline()

    # Get the basic info about the system
    info = infile.readline().split(',')
    dim = int(info[0])
    n = int(info[1])
    years = float(info[2])
    dt = float(info[3])
    radius = float(info[4])
    planet_count = int(info[5])

    infile.readline()

    # Get info about and prepare the planets
    planets = []
    for i in range(planet_count):
        planet = infile.readline().split(",")
        planets.append({"name": planet[1].strip(), "position": np.zeros((n-1, dim))})

    infile.readline()

    # Get the positions at each time step
    for i in range(n-1):
        # Get the position for each planet
        for j in range(planet_count):
            pos = infile.readline().split('=')[1].split(',')
            planets[j]["position"][i] = [float(x.strip()) for x in pos]
    systems.append(planets)


plt.style.use("dark_background")
fig = plt.figure()
ax = fig.gca(projection='3d')

plt.gca().patch.set_facecolor('black')
ax.xaxis.set_pane_color((0, 0, 0, 1.0))
ax.yaxis.set_pane_color((0, 0, 0, 1.0))
ax.zaxis.set_pane_color((0, 0, 0, 1.0))
ax.grid(b=False)

# Plot the sun as a constant dot
ax.scatter([0],[0],[0], label=planets[0]["name"], color="#ffbd38", linewidth=10)

#velocity = [r'$\beta$ = 2.0',r'$\beta$ = 2.5', r'$\beta$ = 2.8', r'$\beta$ = 2.9', r'$\beta$ = 2.95', r'$\beta$ = 2.99', r'$\beta$ = 3.0']


for k in range(file_count):
    for i in range(planet_count):
        pos = systems[k][i]["position"]
        if (planets[i]["name"] == "Sun"): continue
        ax.plot([x[0] for x in pos], [x[1] for x in pos], [x[2] for x in pos], label=velocity[k])


ax.legend()
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
plt.title(r'Different values for $\beta$')
ax.set_xticks([])
ax.set_yticks([])
ax.set_zticks([])
plt.savefig('vary_beta_1.png', dpi=300)
plt.show()




plt.style.use("dark_background")
fig = plt.figure()
ax = fig.gca(projection='3d')

plt.gca().patch.set_facecolor('black')
ax.xaxis.set_pane_color((0, 0, 0, 1.0))
ax.yaxis.set_pane_color((0, 0, 0, 1.0))
ax.zaxis.set_pane_color((0, 0, 0, 1.0))
ax.grid(b=False)
ax.scatter([0],[0],[0], label=planets[0]["name"], color="#ffbd38", linewidth=10)



for k in range(4,7):
    for i in range(planet_count):
        pos = systems[k][i]["position"]
        if (planets[i]["name"] == "Sun"):
            continue
            #if (dim == 3):
                #ax.scatter([x[0] for x in pos], [x[1] for x in pos], [x[2] for x in pos], label=planets[i]["name"], color="#ccff00", linewidth=10)
            #else:
            #ax.scatter([x[0] for x in pos], [x[1] for x in pos], label=planets[i]["name"], color="#ccff00", linewidth=10)

        else:
            if (dim == 3):
                ax.plot([x[0] for x in pos], [x[1] for x in pos], [x[2] for x in pos], label=velocity[k])
            else:
                ax.plot([x[0] for x in pos], [x[1] for x in pos], label=planets[i]["name"])


ax.legend()
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
plt.title(r'Different values for $\beta$')
ax.set_xticks([])
ax.set_yticks([])
ax.set_zticks([])
plt.savefig('vary_beta_2.png', dpi=300)
plt.show()


