#!/usr/bin/env python3
import random
from sys import stdin


s = stdin.readline().strip().split()
pos = 3
if s[0] == "exactly":
    h, w = int(s[1]), int(s[2])
else:
    h = random.randint(int(s[1]), int(s[2]))
    w = random.randint(int(s[3]), int(s[4]))
    pos += 2

print(h, w)

typ = s[pos]
if typ == "random":
    candidates = []
    for i in range(h):
        row = []
        for j in range(w):
            altitude = random.randint(-20, 10)
            row.append(str(altitude))
            if altitude < 0:
                candidates.append((i + 1, j + 1))
        print(' '.join(row))
    x, y = candidates[random.randint(0, len(candidates) - 1)]
    print(x, y)
