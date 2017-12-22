import random
L = 10 ** 11
A = 199
B = 200
R = 300
T = 1200
print(L, A, B, R, T)
w = [L - A * R - 1]
last = w[0]
SZ = 10000
DIST = 1000
ITS = (500000 - 2 - DIST) // SZ
for i in range(ITS):
    for j in range(SZ):
        w.append(last - (A * R + B * T) - j)
    last = w[-SZ]
w.append(w[-SZ] - (A * R + B * T))
for i in range(DIST):
    w.append(random.randint(0, L))
w = list(set(w))
print(len(w))
print(*sorted(w))
