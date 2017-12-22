#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")

for dog in range(2):
    line = stdin.readline()
    assert oneint.match(line)
    n = int(line)
    assert 2 <= n <= 10 ** 5

    prev = (-1, -1)
    for test in range(n):
        line = stdin.readline()
        assert twoint.match(line)
        x, y = list(map(int, line.split()))
        assert 0 <= x <= 10 ** 4 and 0 <= y <= 10 ** 4
        assert prev != (x, y)
        prev = (x, y)

assert len(stdin.readline()) == 0
sys.exit(42)
