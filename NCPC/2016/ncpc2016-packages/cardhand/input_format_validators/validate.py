#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
card = "[2-9TJQKA][hscd]"
sentence = re.compile(integer + "( [a-z]+)+\n")
twoint = re.compile(integer + " " + integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 52

line = stdin.readline()
assert len(line) == 3*n

assert re.compile("(" + card + "[ \n]){" + str(n) + "}").match(line)
assert line[-1] == "\n"
for i in range(0,n):
    for j in range(i+1,n):
        assert line[3*i:3*i+2] != line[3*j:3*j+2]

assert len(stdin.readline()) == 0
sys.exit(42)
