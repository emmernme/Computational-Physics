"""
Program to plot the results from the methods.
"""
import matplotlib.pyplot as plt
import numpy as np


#N = [5, 7, 10, 12, 15, 17, 20, 22, 25, 27, 30, 32, 35]

N = np.linspace(5, 35, 13)


exact = 0.192765

c_lag = [0.170492, 0.154422, 0.177081, 0.187305, 0.193285, 0.194396,
 0.194786, 0.194813, 0.194804, 0.194795, 0.194779, 0.194764, 0.194734]
diff_lag = [exact-c_lag[0], exact-c_lag[1], exact-c_lag[2], exact-c_lag[3],
 exact-c_lag[4], exact-c_lag[5], exact-c_lag[6], exact-c_lag[7], exact-c_lag[8],
  exact-c_lag[9], exact-c_lag[10], exact-c_lag[11], exact-c_lag[12]]


c_leg = [0.264249, 0.329525, 0.071980, 0.099032, 0.239088, 0.222933,
 0.156139, 0.162727, 0.196817, 0.193524, 0.177283, 0.179292, 0.189923]
diff_leg = [exact-c_leg[0], exact-c_leg[1], exact-c_leg[2], exact-c_leg[3],
 exact-c_leg[4], exact-c_leg[5], exact-c_leg[6], exact-c_leg[7], exact-c_leg[8],
  exact-c_leg[9], exact-c_leg[10], exact-c_leg[11], exact-c_leg[12]]

plt.scatter(N, c_lag, label = 'Calculated Laguerre')
plt.scatter(N, c_leg, label = 'Calculated Legendre')
plt.axhline(y = exact, label = 'Exact value')
plt.legend()
plt.title('Calculated values vs number of iterations')
plt.xlabel('N[#]')
plt.ylabel('Calculated Integralvalue')
plt.show()


plt.scatter(N, diff_lag, label = 'Diff Laguerre')
plt.scatter(N, diff_leg, label = 'Diff Legendre')
plt.axhline(y = 0)
plt.legend()
plt.title('Diff between exact and calculated value vs number of iterations')
plt.xlabel('N[#]')
plt.ylabel('Diff (exact - calculated)')
plt.show()
