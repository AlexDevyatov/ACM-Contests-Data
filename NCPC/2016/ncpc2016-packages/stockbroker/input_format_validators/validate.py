#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)\n"

line = stdin.readline()
assert re.match(integer, line)
d = int(line)
assert 1 <= d <= 365
for i in range(0, d):
    line = stdin.readline()
    assert re.match(integer, line)
    p = int(line)
    assert 1 <= p <= 500
assert len(stdin.readline()) == 0
sys.exit(42)
