import matplotlib.pyplot as plt
import numpy as np

alpa = 2

N = 100

x1 = linspace
x2 = linspace
y1 = linspace
y2 = linspace
z1 = linspace
z2 = linspace

def wave_function(x1, x2, y1, y2, z1, z2):

    r1 = sqrt(x1**2 + y1**2 + z1**2)
    r2 = sqrt(x2**2 + y2**2 + z2**2)

    deno = abs(r1 - r2)

    return exp(-2*alpha*(r1 - r2)) / deno
