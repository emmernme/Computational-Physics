# Give files though arguments:
# python system_plot_multiple.py file1.dat file2.dat file3.dat

import matplotlib.pyplot as plt
import numpy as np
import sys
from mpl_toolkits.mplot3d import Axes3D

# Get the files from the arguments
file_count = len(sys.argv) - 1
files = []
for i in range(file_count):
    files.append(sys.argv[i+1])

# Set up a dict for the systems imported
systems = {}
for file in files:
    # Open the file
    infile = open(file, 'r')
    infile.readline() # Skip info line

    # Get the basic info about the system
    info = infile.readline().split(',')
    dim = int(info[0])
    n = int(info[1])
    years = float(info[2])
    dt = float(info[3])
    radius = float(info[4])
    planet_count = int(info[5])
    beta = float(info[6])
    title = info[7].strip()

    infile.readline() # Skip info line

    # Get info about, and prepare, the planets
    planets = []
    for i in range(planet_count):
        planet = infile.readline().split(",")
        planets.append({"name": planet[1].strip(), "position": np.zeros((n-1, dim))})

    infile.readline() # Skip info line

    # Get the positions at each time step
    for i in range(n-1):
        # Get the position for each planet
        for j in range(planet_count):
            pos = infile.readline().split('=')[1].split(',')
            planets[j]["position"][i] = [float(x.strip()) for x in pos]
    systems[title] = planets

# Set up the plot as we like it
plt.style.use("dark_background")
fig = plt.figure(figsize=(10.8, 7.2))
ax = fig.gca(projection='3d')

plt.gca().patch.set_facecolor('black')
ax.xaxis.set_pane_color((0, 0, 0, 1.0))
ax.yaxis.set_pane_color((0, 0, 0, 1.0))
ax.zaxis.set_pane_color((0, 0, 0, 1.0))
ax.grid(b=False)

# Plot the sun as a constant dot
ax.scatter([0],[0],[0], label="Sun", color="#ffbd38", linewidth=10)

# Plot each planet in each system
for title, planets in systems.items():
    for i in range(planet_count):
        pos = planets[i]["position"]
        if (planets[i]["name"] == "Sun"): continue
        ax.plot([x[0] for x in pos], [x[1] for x in pos], [x[2] for x in pos], label=title + ", " + planets[i]["name"])

# Customize the plot
ax.legend(loc="upper right") # Speeds up plot
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
ax.set_xticks([])
ax.set_yticks([])
ax.set_zticks([])
fig.tight_layout()

#plt.savefig('vary_beta_1.png', dpi=300)
plt.show()


