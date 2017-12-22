#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
f = int(line)
assert 1 <= f <= 10

for x in range(f):
    line = stdin.readline()
    assert twoint.match(line)
    t, n = list(map(int, line.split()))

    assert 1 <= t <= 10000
    assert 1 <= n <= 100

    last = -1
    for i in range(n):
        line = stdin.readline()
        assert twoint.match(line)
        s, e = list(map(int, line.split()))
        assert last < s < e
        last = e

    assert last <= 10 ** 6

assert len(stdin.readline()) == 0
sys.exit(42)
