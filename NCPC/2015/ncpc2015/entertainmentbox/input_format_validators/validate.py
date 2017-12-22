#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert twoint.match(line)
n, k = map(int, line.split())
assert 1 <= k < n <= 100000

for x in range(n):
    line = stdin.readline()
    assert twoint.match(line)
    start, end = list(map(int, line.split()))
    assert 0 <= start < end <= 10 ** 9

assert len(stdin.readline()) == 0
sys.exit(42)
