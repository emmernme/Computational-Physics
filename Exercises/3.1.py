# Compute first derivative of f(x) = tan^-1(x)
import numpy as np
import matplotlib.pyplot as plt


# 3.1.1 Find the step length that gives the smallest value epsillon
def eps_2c(h):
    x = np.sqrt(2)
    return (np.abs(1/3 - (np.arctan(x + h) - np.arctan(x))/h), h)
def eps_3c(h):
    x = np.sqrt(2)
    return (np.abs(1/3 - (np.arctan(x + h) - np.arctan(x - h))/(2*h)), h)

h = np.linspace(1e-12, 1e-10, 10000)

eps2c_arr = eps_2c(h)
eps3c_arr = eps_3c(h)

err2c_min_index = eps2c_arr[0].argmin()
err2c_min_h = eps2c_arr[1][err2c_min_index]
print("min(e_2c) = " + str(eps2c_arr[0][err2c_min_index]) + ", h = " + str(err2c_min_h))

err3c_min_index = eps3c_arr[0].argmin()
err3c_min_h = eps3c_arr[1][err3c_min_index]
print("min(e_3c) = " + str(eps3c_arr[0][err3c_min_index]) + ", h = " + str(err3c_min_h))

def f(x):
    return np.arctan(x)
def O(h):
    return 0

def Df_2c(x, h):
    return (f(x + h) - f(x)) * 1/h + O(h)
def Df_3c(x, h):
    return (f(x + h) - f(x - h)) * 1/(2*h) + O(h**2)

