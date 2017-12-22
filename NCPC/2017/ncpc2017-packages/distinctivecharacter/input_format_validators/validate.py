#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
first = re.compile(integer + " " + integer + "\n")
bits = "[01]+"
player = re.compile(bits + "\n")

line = stdin.readline()
assert first.match(line)
n, k = list(map(int, line.split()))
assert 1 <= n <= 10**5 and 1 <= k <= 20

for item in range(n):
    line = stdin.readline()
    assert player.match(line)
    line = line.strip()
    assert len(line) == k

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
