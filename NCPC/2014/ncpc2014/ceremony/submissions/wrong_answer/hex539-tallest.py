#!/usr/bin/env python3
import sys

h = map(int, (sys.stdin.readlines()[1]).split())
print min(len(h), max(h))

