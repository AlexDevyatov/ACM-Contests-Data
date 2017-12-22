#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")
threeint = re.compile("(" + integer + " ){2}" + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
C,n = map(int, line.split())
assert 1 <= C <= 10**9
assert 2 <= n <= 100

for t in range(n):
  line = stdin.readline()
  assert threeint.match(line)
  for x in map(int, line.split()):
    assert 0 <= x <= 10**9

assert len(stdin.readline()) == 0
sys.exit(42)
