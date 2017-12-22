#!/usr/bin/python
from sys import stdin
import re, sys

integer = "(0|[1-9]\d*)"
line = stdin.readline()
assert re.match(integer + " " + integer  + " " + integer + "\n", line)
b, n, e = [int(a) for a in line.split()]
assert 2 <= b+n+e <= 100000
assert (b+n+e)%2 == 0

line = stdin.readline()
assert re.match(integer + " " + integer  + " " + integer + "\n", line)
sb, sn, se = [int(a) for a in line.split()]
assert 1 <= sb < sn < se <= 1000

line = stdin.readline()
assert re.match("(" + integer + " )*" + integer + "\n", line)
c = [int(a) for a in line.split()]
assert len(c) == (b+n+e)//2
for ci in c:
    assert 1 <= ci <= 100000

assert len(stdin.readline()) == 0
sys.exit(42)
