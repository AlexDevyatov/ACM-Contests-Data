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
assert 2 <= n <= 10 ** 5

line = stdin.readline()
assert manyint.match(line)
a = list(map(int, line.split()))
assert len(a) == n
for x in a:
    assert 1 <= x <= 10 ** 6

assert len(stdin.readline()) == 0
sys.exit(42)
