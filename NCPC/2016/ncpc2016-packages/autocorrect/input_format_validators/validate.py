#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
wordpat = re.compile("[a-z]+\n")
twoint = re.compile(integer + " " + integer + "\n")

inputsize = 0
line = stdin.readline()
inputsize += len(line)
assert twoint.match(line)
n, m = list(map(int, line.split()))
assert 1 <= n <= 10 ** 5 and 1 <= m <= 10 ** 5
dic=set()
for i in range(0,n):
    line = stdin.readline()
    inputsize += len(line)
    assert wordpat.match(line)
    word = line.strip()
    assert word not in dic
    dic.add(word)
for i in range(0,m):
    line = stdin.readline()
    inputsize += len(line)
    assert wordpat.match(line)

assert inputsize <= 1024 * 1024
assert len(stdin.readline()) == 0
sys.exit(42)
