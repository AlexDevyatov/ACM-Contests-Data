#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
inputline = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert inputline.match(line)
l, r = list(map(int, line.split()))
assert 0 <= l <= 20 and 0 <= r <= 20
assert len(stdin.readline()) == 0
sys.exit(42)
