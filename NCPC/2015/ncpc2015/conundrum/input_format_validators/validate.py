#!/usr/bin/env python3
from sys import stdin
import re
import sys

string = re.compile("[A-Z]+\n")

line = stdin.readline()
assert string.match(line)
assert len(line) % 3 == 1
assert len(line) <= 301

assert len(stdin.readline()) == 0
sys.exit(42)
