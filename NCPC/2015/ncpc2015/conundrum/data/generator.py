#!/usr/bin/env python3
import random
from sys import stdin


def flip(percentage, char):
    if random.randint(0, 100) <= percentage:
        return char
    return chr(ord('A') + random.randint(0, 25))

s = stdin.readline().strip().split()
if s[0] == "exactly":
    n = int(s[1])
else:
    n = random.randint(int(s[1]), int(s[2]))

percentage = random.randint(0, 100)

res = [flip(percentage, x) for x in "PER" * n]

print(''.join(res))
