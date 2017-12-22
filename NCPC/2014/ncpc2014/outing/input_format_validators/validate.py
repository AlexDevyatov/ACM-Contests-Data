#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, k = list(map(int, line.split()))
assert 1 <= n <= 1000
assert 1 <= k <= n

line = stdin.readline()
assert manyint.match(line)
x = list(map(int, line.split()))
assert len(x) == n
for i in x:
  assert 1 <= i <= n

assert len(stdin.readline()) == 0
sys.exit(42)
