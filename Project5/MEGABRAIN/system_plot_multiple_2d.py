# Give files though arguments:
# python system_plot_muliple_2d.py file1.dat file2.dat file3.dat
# Can plot around 2e7 points in total without too much trouble
import matplotlib.pyplot as plt
import numpy as np
import sys

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
#mpl.rcParams['axes.prop_cycle'] = cycler(color='brgcmyk')
fig = plt.figure(figsize=(10.8, 7.2))
ax = fig.gca()
plt.gca().patch.set_facecolor('black')
ax.grid(b=False)

# Plot the sun as a constant dot (saving memory and CPU)
ax.scatter([0],[0], label="Sun", color="#ffbd38", linewidth=10)

# Plot each planet in each system
for title, planets in systems.items():
    for i in range(planet_count):
        pos = planets[i]["position"]
        if (planets[i]["name"] == "Sun"): continue
        ax.plot([x[0] for x in pos], [x[1] for x in pos], linewidth=1, label=planets[i]["name"] + ", " + title)

# Customize the plot
ax.legend(loc="upper right") # Speeds up plot
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_xticks([])
ax.set_yticks([])
fig.tight_layout()

# Set the zoom limits to focus on Mercury's perihelion position
ax.set_xlim([-0.005,0.31])
ax.set_ylim([-0.26,0.26])

plt.savefig('Mercury_perihelion_zoom.png', dpi=300)
plt.show()


