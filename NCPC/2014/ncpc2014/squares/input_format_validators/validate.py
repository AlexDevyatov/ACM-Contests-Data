#!/usr/bin/python
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
fourint = re.compile(integer + " " +integer + " " + integer + " " +integer + "\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 2000

l = []
for i in range(n):
    line = stdin.readline()
    assert fourint.match(line)
    a = list(map(int, line.split()))
    for j in range(4):
        assert -10000 <= a[j] <= 10000
    assert ((a[0]!=a[2]) or (a[1]!=a[3]))
    l.append([a[0],a[1],a[2],a[3]])

for j in range(n):
    for i in range(j):
        p1=(l[i][2]-l[i][0])*(l[j][1]-l[i][1])-(l[i][3]-l[i][1])*(l[j][0]-l[i][0])
        p2=(l[i][2]-l[i][0])*(l[j][3]-l[i][1])-(l[i][3]-l[i][1])*(l[j][2]-l[i][0])
        assert ((p1!=0) or (p2!=0))

assert len(stdin.readline()) == 0
sys.exit(42)
