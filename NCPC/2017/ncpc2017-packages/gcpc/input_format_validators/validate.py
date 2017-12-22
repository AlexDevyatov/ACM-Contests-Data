#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
first = re.compile(integer + " " + integer + "\n")
submit = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert first.match(line)
n, m = list(map(int, line.split()))
assert 1 <= n <= 10**5 and 1 <= m <= 10**5

for event in range(m):
    line = stdin.readline()
    assert submit.match(line)
    t, p = list(map(int, line.split()))
    assert 1 <= t <= n and 1 <= p <= 1000

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
