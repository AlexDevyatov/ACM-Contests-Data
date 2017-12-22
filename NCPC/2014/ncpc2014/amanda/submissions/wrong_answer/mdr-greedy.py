#!/usr/bin/env python3

# Author: Markus Dregi
# Greedy solution that propagates for edges with requirement 0 and 2.
# In the components with only requirements equal to one, it builds a lounge in
# the highest degree vertex

import sys
from sys import stdin
from Queue import Queue,PriorityQueue

def failure():
    print("impossible")
    sys.exit(0)

def propagate(pos, graph, lounge):
    q = Queue()
    q.put(pos)

    while not q.empty():
        pos = q.get()

        for r,b in graph[pos]:
            if lounge[b] < 0:
                lounge[b] = r-lounge[pos]
                if lounge[b] < 0 or lounge[b] > 1:
                    failure()

                q.put(b)
            elif lounge[pos] + lounge[b] is not r:
                failure()

n,m = [int(x) for x in stdin.readline().split()]
graph = [[] for i in range(n)]

for i in range(m):
    a,b,r = [int(x) for x in stdin.readline().split()]
    a = a-1
    b = b-1
    graph[a].append((r,b))
    graph[b].append((r,a))

lounge = [-1]*n

for a in range(n):
    if lounge[a] >= 0:
        continue

    for r,b in graph[a]:
        if r is not 1:
            lounge[a] = r/2
            propagate(a, graph, lounge)

pri = PriorityQueue()
for v in range(n):
    pri.put((-len(graph[v]), v))

while not pri.empty():
    d, v = pri.get()
    d = -d
    if lounge[v] >= 0:
        continue

    lounge[v] = 1
    propagate(v, graph, lounge)

print(sum(lounge))
