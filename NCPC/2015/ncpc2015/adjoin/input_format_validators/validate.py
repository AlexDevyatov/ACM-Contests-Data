#!/usr/bin/env python3
from sys import stdin
import re
import sys


def join(e, a, b):
    a, b = find(e, a), find(e, b)
    if a == b:
        return False
    if e[a] > e[b]:
        a, b = b, a
    e[a] += e[b]
    e[b] = a
    return True


def find(e, x):
    if e[x] < 0:
        return x
    e[x] = find(e, e[x])
    return e[x]


integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, m = map(int, line.split())
assert 0 <= m < n <= 100000

uf = [-1] * n
for x in range(m):
    line = stdin.readline()
    assert twoint.match(line)
    a, b = list(map(int, line.split()))
    assert 0 <= a < n and 0 <= b < n
    assert a != b
    assert join(uf, a, b)  # check that we are not creating a cycle

assert len(stdin.readline()) == 0
sys.exit(42)
