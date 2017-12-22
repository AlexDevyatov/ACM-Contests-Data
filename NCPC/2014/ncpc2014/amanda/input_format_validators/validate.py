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
assert twoint.match(line) # n, m <= 200 000
line = line.split()
n = int(line[0])
m = int(line[1])

assert 1 <= n <= 200000 # n number of vertices
assert 1 <= m <= 200000 # m number of vertices

edges = {}


neighbors = {}

for i in range(m):
    line = stdin.readline()
    assert threeint.match(line)
    line = line.split()
    a = int(line[0])
    b = int(line[1])
    c = int(line[2])
    assert a != b # simple graph
    assert 1 <= a <= n # a is a vertex
    assert 1 <= b <= n # b is a vertex
    assert a != b # no self-loops
    assert 0 <= c <= 2 # c is in {0,1,2}
    if a in neighbors:
        assert b not in neighbors[a] # no multiple edges
        neighbors[a].add(b)
    else:
        neighbors[a] = set([b])

    if b in neighbors:
        assert a not in neighbors[b] # no multiple edges
        neighbors[b].add(a)
    else:
        neighbors[b] = set([a])
    x = min(a,b)
    y = max(a,b)
    assert (x,y) not in edges
    edges[(x,y)] = c


# checking end of input
assert len(stdin.readline()) == 0

# checking symmetry
for i in range(1,n+1):
    if i in neighbors:
        ni = neighbors[i]
        for j in ni:
            assert i in neighbors[j]

sys.exit(42)
