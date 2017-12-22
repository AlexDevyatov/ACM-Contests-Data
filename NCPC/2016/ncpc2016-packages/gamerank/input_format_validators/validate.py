#!/usr/bin/env python3
from sys import stdin
import re
import sys

gamesequence = re.compile("[WL]{1,10000}\n")

line = stdin.readline()
assert gamesequence.match(line)
assert len(stdin.readline()) == 0
sys.exit(42)
