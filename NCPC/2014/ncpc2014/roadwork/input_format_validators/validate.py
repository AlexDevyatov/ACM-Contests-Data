#!/usr/bin/python
from sys import stdin
import re, sys

integerExp = '(0|-?[1-9]\\d*)'
floatExp = '(' + integerExp + '(.\\d+)?)'
integerExpRe = re.compile(integerExp)

# First line: "t n"
lineRe = re.compile(integerExp + ' ' + integerExp + '\n')
line = stdin.readline()
assert(lineRe.match(line))
(t, n) = (int(i) for i in line[:-1].split(' ',1))
assert(4 <= t <= 180)
assert(1 <= n <= 250)

# n lines: "d a i"
lineRe = re.compile('[WE] ' + ' '.join([integerExp]*2) + '\n')
prevA = 0
for nIdx in range(n):
    line = stdin.readline()
    assert(lineRe.match(line))
    (d, a, r) = (x for x in line[:-1].split(' ',2))
    a = int(a)
    r = int(r)
    assert(d == 'E' or d == 'W')
    assert(0 <= prevA <= a < 86400)
    assert(0 <= r <= 3600)
    prevA = a

assert(len(stdin.readline()) == 0)
sys.exit(42)
