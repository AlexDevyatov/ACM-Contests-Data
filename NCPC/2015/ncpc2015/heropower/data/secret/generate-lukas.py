#!/usr/bin/env python3
from random import randint


def tomillis(x):
    return 800 + randint(-300, 300)

n = 50000
p = 100

print("%d %d" % (n, p))

t = [tomillis(i) for i in range(n)]
for i in range(1, n):
    t[i] += t[i - 1]
print(" ".join(map(str, t)))

length = n // p
for i in range(p):
    a, b = i * length, (i + 1) * length
    # 13-huge.in
    # print(tomillis(a), tomillis(b - 1))
    # 15-huge.in
    f, s = t[a], t[(a + b) // 2]
    print(f, s)
