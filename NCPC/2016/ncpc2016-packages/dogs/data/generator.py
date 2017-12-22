#!/usr/bin/env python3
import random
from sys import stdin


def prin(a):
    print(len(a))
    for x in a:
        print("%d %d" % (x[0], x[1]))


def plus(a, b):
    return (a[0] + b[0], a[1] + b[1])


def generate_randwalk(n):
    points = [(5000 + random.randint(-500, 500), 5000 + random.randint(-500, 500))]
    for i in range(n - 1):
        diff = (0, 0)
        while diff == (0, 0):
            diff = (random.randint(-13, 13), random.randint(-13, 13))
        points.append(plus(points[-1], diff))
    return points


s = stdin.readline().strip().split()
pos = 3
if s[0] == "exactly":
    n, m = int(s[1]), int(s[2])
else:
    n = random.randint(int(s[1]), int(s[2]))
    m = random.randint(int(s[3]), int(s[4]))
    pos += 2

inp_type = s[pos]  # randwalk | ... TBD

if inp_type == "randwalk":
    prin(generate_randwalk(n))
    prin(generate_randwalk(m))
# elif inp_type == ""
