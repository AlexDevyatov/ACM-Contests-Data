#!/usr/bin/python2
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"

line = stdin.readline()
assert re.match(integer + "\n", line)
n = int(line)
assert 1 <= n <= 100000

for i in range(n):
    line = stdin.readline()
    assert re.match(integer + " " + integer + "\n", line)
    x, y = [int(x) for x in line.split()]
    assert 0 <= x and x <= 10000
    assert 0 <= y and y <= 10000

line = stdin.readline()
assert re.match(integer + "\n", line)
m = int(line)
assert 1 <= m <= 20000

for i in range(m):
    line = stdin.readline()
    assert re.match(integer + " " + integer + " " + integer + "\n", line)
    x, y, r = map(int, line.split())
    assert 0 <= x and x <= 10000
    assert 0 <= y and y <= 10000
    assert 1 <= r and r <= 100

# Nothing to report
sys.exit(42)
