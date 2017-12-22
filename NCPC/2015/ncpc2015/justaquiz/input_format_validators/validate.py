#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")
questionanswer = re.compile("[!->@-~]+( [!->@-~]+)*\\? [!-~]+\n")

line = stdin.readline()
assert twoint.match(line)
t, n = map(int, line.split())
assert 1 <= t <= 100 and 1 <= n <= 10**5

inputsize = 0
for i in range(n):
    line = stdin.readline()
    assert questionanswer.match(line)
    inputsize += sum(len(s) for s in line.split())-1 # -1 for a question mark

assert inputsize<=100000

sys.exit(42)
