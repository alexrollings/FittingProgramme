import matplotlib.pyplot as plt
import numpy as np
import math

fig = plt.figure()
total_yield = 40000
# x = shared yield
x = np.arange(0, total_yield, 2000)
# print(x)
xerr = np.sqrt(x)
# print(xerr)
# y = error correction (corrected error / fit error)
# y = pull width of total signal yield
y = x*(math.sqrt(2)/total_yield) + (total_yield - x)/total_yield
# print(y)
# Overlay with function:
# f(x) = x*(math.sqrt(2)/total_yield) + (total_yield - x)/total_yield
# Propagate uncertainties

plt.errorbar(x, y, xerr=xerr)
# Double events in box yield or single?
plt.xlabel('Box yield')
plt.ylabel('Pull width')
plt.show()

