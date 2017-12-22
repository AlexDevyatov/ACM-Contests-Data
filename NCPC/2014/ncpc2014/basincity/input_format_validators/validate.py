#!/usr/bin/env python2
from sys import stdin
import sys
import re

integer = "(0|-?[1-9]\d*)"
floating = integer + "?(\.\d+)?"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")
threeint = re.compile("(" + integer + " ){2}" + integer + "\n")
fourint = re.compile("(" + integer + " ){3}" + integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")
string = re.compile("[a-z]+\n")

line = stdin.readline()
assert oneint.match(line)
k = int(line)
assert 0 <= k <= 15 # k at most 15

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 100000 # n at most 100 000

neighbors = {}

for i in range(1,n+1):
    line = stdin.readline()
    assert manyint.match(line)
    line = line.split()
    neig = set()
    for j in range(len(line)):
        line[j] = int(line[j])
        if j > 0:
            assert 1 <= line[j] <= n
            assert line[j] != i
            assert line[j] not in neig
            neig.add(line[j])

    d = line[0]
    assert d <= 4 # degree constraints

    assert len(line) == d + 1 # degree is first int

    neighbors[i] = set(line[1:])

# checking end of input
assert len(stdin.readline()) == 0

# checking symmetry
for i in range(1,n+1):
    ni = neighbors[i]
    for j in ni:
        assert i in neighbors[j]

sys.exit(42)
