#!/usr/bin/python
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " +integer + "\n")

degs = []
FU = []
totEdges = []
isDeg3 = []
isPath = []

def FUFind(t):
    if FU[t]<0:
        return t
    else:
        r = FUFind(FU[t])
        FU[t] = r
        return r

def FUJoin(a,b):
    a = FUFind(a)
    b = FUFind(b)
    if a==b:
        return None
    if FU[a]>FU[b]:
        a, b = b, a
    FU[a]+=FU[b]
    FU[b]=a


line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 500

crds = []
for i in range(n):
    line = stdin.readline()
    assert twoint.match(line)
    a = list(map(int, line.split()))
    assert -10000 <= a[0] <= 10000
    assert -10000 <= a[1] <= 10000
    crds.append((a[0],a[1]))
    FU.append(-1)
    degs.append(0)
    totEdges.append(0)
    isDeg3.append(False)
    isPath.append(False)

crds.sort()

for i in range(len(crds)-1):
    assert crds[i] != crds[i+1]


line = stdin.readline()
assert oneint.match(line)
m = int(line)
assert 0 <= m <= 2000

edges = []

for i in range(m):
    line = stdin.readline()
    assert twoint.match(line)
    a = list(map(int, line.split()))
    assert 1 <= a[0] <= n
    assert 1 <= a[1] <= n
    assert a[0] != a[1]
    degs[a[0]-1]+=1
    degs[a[1]-1]+=1
    FUJoin(a[0]-1,a[1]-1)
    if a[0]<a[1]:
        edges.append((a[0],a[1]))
    else:
        edges.append((a[1],a[0]))

edges.sort()

for i in range(len(edges)-1):
    assert edges[i] != edges[i+1]

for i in range(n):
    if (degs[i]>2):
        isDeg3[FUFind(i)]=True

for i in range(len(edges)):
    totEdges[FUFind(edges[i][0])]+=1

for i in range(n):
    if ((FU[i]<0) and (-FU[i]==totEdges[i]+1) and (not isDeg3[i])):
        isPath[i]=True

line = stdin.readline()
assert oneint.match(line)
l = int(line)
assert 1 <= l <= (n*(n-1))/2

for i in range(l):
    line = stdin.readline()
    assert twoint.match(line)
    a = list(map(int, line.split()))
    assert 1 <= a[0] <= n
    assert 1 <= a[1] <= n
    assert a[0] != a[1]
    assert FUFind(a[0]-1) == FUFind(a[1]-1)
    assert (not isPath[FUFind(a[0]-1)])

assert len(stdin.readline()) == 0
sys.exit(42)
