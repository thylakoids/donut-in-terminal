import math
import numpy as np
print("\x1b[2J", end='')
r1 = 1
r2 = 2

circle = []
for theta in np.linspace(0, 6.28, 30):
    circle.append(np.array([r1, 0, 0]) + np.array([r1 * math.cos(theta), r1 * math.sin(theta), 0]))



