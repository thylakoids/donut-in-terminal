import time
import math
A, B = 0, 0
print("\x1b[2J", end='')
while True:
    z = [0] * 1760  # z buffer
    b = [' '] * 1760  # buffer frame
    for theta in range(0, 628, 7):  # theta
        for φ in range(0, 628, 2):  # φ
            sin_phi = math.sin(φ)
            cos_theta = math.cos(theta)  # cos(theta)
            sin_A = math.sin(A)
            sin_theta = math.sin(theta)
            cos_A = math.cos(A)
            h = cos_theta + 2  # r1*cos(theta) + r2
            D = 1 / (sin_phi * h * sin_A + sin_theta * cos_A + 5)  # coordinate z
            cos_phi = math.cos(φ)
            cos_B = math.cos(B)
            sin_B = math.sin(B)
            t = sin_phi * h * cos_A - sin_theta * sin_A

            x = int(40 + 30 * D * (cos_phi * h * cos_B - t * sin_B))  # which column
            y = int(12 + 15 * D * (cos_phi * h * sin_B + t * cos_B))  # which row
            o = int(x + 80 * y)  # index in buffer
            N = int(8 * ((sin_theta * sin_A - sin_phi * cos_theta * cos_A) * cos_B - sin_phi *
                    cos_theta * sin_A - sin_theta * cos_A - cos_phi * cos_theta * sin_B))  # luminance
            if 22 > y and y > 0 and x > 0 and 80 > x and D > z[o]:
                z[o] = D
                b[o] = ".,-~:;=!*#$@"[N if N > 0 else 0]
    print('\x1b[H', end='')
    for k in range(1761):
        print((b[k] if k % 80 else '\n'), end='')
    A += 0.00004*1761
    B += 0.00002*1761
    # time.sleep(0.1)
