#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
manyint = re.compile("(" + integer + " )*" + integer + "\n")

for player in range(2):
    line = stdin.readline()
    assert manyint.match(line)
    a = list(map(int, line.split()))
    assert len(a) == 4
    for x in a:
        assert 1 <= x <= 100

    for i in range(0, 3, 2):
        assert a[i] + 2 < a[i + 1]

assert len(stdin.readline()) == 0
sys.exit(42)
