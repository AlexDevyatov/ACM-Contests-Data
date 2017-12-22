#!/usr/bin/env python3
import random
from sys import stdin

MAX = 100

s = stdin.readline().strip().split()
if s[0] == "exactly":
    sides = int(s[1])
else:
    sides = random.randint(int(s[1]), int(s[2]))

assert sides >= 4
if sides > 98:
    sides = 98


def generate():
    w = random.randint(3, sides - 1)
    x = random.randint(1, MAX - w)
    return [x, x + w]


def generate2():
    return generate() + generate()

tie = random.randint(0, 4) == 0

res = [[], []]
if not tie:
    while True:
        if s[0] == "close":
            res = [generate2(), generate2()]
            if abs(sum(res[0]) - sum(res[1])) == 1:
                break
        else:
            res = [generate2(), generate2()]
            if abs(sum(res[0]) - sum(res[1])) == 0:
                break
else:
    while True:
        res = [generate2(), generate2()]
        if sum(res[0]) == sum(res[1]):
            break

for i in range(2):
    print(" ".join(str(x) for x in res[i]))
