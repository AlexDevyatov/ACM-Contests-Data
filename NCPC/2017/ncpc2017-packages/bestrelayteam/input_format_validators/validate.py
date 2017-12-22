#!/usr/bin/python
from sys import stdin
import re, sys

integer = "(0|[1-9]\d*)"
name = "[A-Z]{2,20}"
time = "(0|[1-9]\d*)\.\d\d"

line = stdin.readline()
assert re.match("^" + integer + "\n", line)
n = int(line)
assert 4 <= n <= 500

names = set()

for i in range(0,n):
    line = stdin.readline()
    assert re.match("^" + name + " " + time + " " + time + "\n", line)
    surname, t1, t2 = line.split()
    assert not surname in names
    names.add(surname)
    t1 = float(t1)
    t2 = float(t2)
    assert 8.00 <= t2 <= t1 < 20.00

assert len(stdin.readline()) == 0
sys.exit(42)
