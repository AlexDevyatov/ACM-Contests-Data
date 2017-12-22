#!/usr/bin/env python3
from sys import stdin
import re
import sys

MAX_DIM = 500
MAX_DEPTH = 10**6

integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
h, w = list(map(int, line.split()))
assert 1 <= h <= MAX_DIM and 1 <= w <= MAX_DIM

grid = []
for i in range(h):
    line = stdin.readline()
    assert manyint.match(line)
    a = list(map(int, line.split()))
    assert len(a) == w
    for x in a:
        assert -MAX_DEPTH <= x <= MAX_DEPTH
    grid.append(a)

line = stdin.readline()
assert twoint.match(line)
sx, sy = list(map(int, line.split()))
assert 1 <= sx <= h and 1 <= sy <= w
assert grid[sx-1][sy-1] < 0

assert len(stdin.readline()) == 0
sys.exit(42)
