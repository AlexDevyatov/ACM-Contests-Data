#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"

line = stdin.readline()
assert re.match(integer+'\n', line)
d = int(line)
assert 0 <= d <= 359

line = stdin.readline()
assert re.match(integer+'\n', line)
d = int(line)
assert 0 <= d <= 359

assert stdin.readline() == ''

sys.exit(42)
