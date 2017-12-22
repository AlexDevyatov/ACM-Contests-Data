#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
first = re.compile(integer + " " + integer + " " + integer + "\n")
stroke = re.compile(integer + " " + integer + " " + integer + " " + integer + "\n")

line = stdin.readline()
assert first.match(line)
n, m, q = list(map(int, line.split()))
assert 1 <= n <= 1000 and 1 <= m <= 1000 and 1 <= q <= 10**4

for query in range(q):
    line = stdin.readline()
    assert stroke.match(line)
    y1, x1, y2, x2 = list(map(int, line.split()))
    assert 1 <= y1 <= y2 <= n and 1 <= x1 <= x2 <= m
    assert y1 == y2 or x1 == x2

assert sys.stdin.readline() == '' # No trailing input

sys.exit(42)
