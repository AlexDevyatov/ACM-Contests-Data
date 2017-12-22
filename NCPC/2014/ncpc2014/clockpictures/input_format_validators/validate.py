#!/usr/bin/env python3
from sys import stdin
import re
import sys

oneint = re.compile("[1-9]\d*\n")
integer = "(0|-?[1-9]\d*)"
manyint = re.compile("(" + integer + " )*" + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 2 <= n <= 2 * (10 ** 5)

for clock in [1, 2]:
  line = stdin.readline()
  assert manyint.match(line)
  a = list(map(int, line.split()))
  assert len(a) == n
  assert len(set(a)) == n
  for x in a:
      assert 0 <= x < 360000

assert len(stdin.readline()) == 0
sys.exit(42)
