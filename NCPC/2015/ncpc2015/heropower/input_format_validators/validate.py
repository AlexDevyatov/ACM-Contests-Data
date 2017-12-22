#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, p = map(int, line.split())
assert 1 <= n <= 50000
assert 0 <= p <= 100

line = stdin.readline()
assert manyint.match(line)
t = list(map(int, line.split()))
assert len(t) == n
assert sorted(t)

assert 0 <= t[0] and t[-1] <= 5 * (10 ** 7)

notes = set(t)
old_e = -1
for i in range(p):
    line = stdin.readline()
    assert twoint.match(line)
    s, e = list(map(int, line.split()))
    assert 0 <= s < e <= 5 * (10 ** 7)
    assert s in notes and e in notes
    assert old_e < s
    old_e = e

assert len(stdin.readline()) == 0
sys.exit(42)
