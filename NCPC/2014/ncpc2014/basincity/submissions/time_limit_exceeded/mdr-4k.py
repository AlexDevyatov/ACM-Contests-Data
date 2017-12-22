#!/usr/bin/env python
# -*- coding: utf-8
# Solution by Markus Dregi
# 4^k n solution that solves connected components independently
# Branches on lowest degree vertex

import sys
from sys import stdin

def findcomponent(v):
    if searched[v]:
        return

    cc.append(v)
    searched[v] = True
    for u in graph[v]:
        findcomponent(u)

def getlowdeg():
    u = -1
    deg = 10
    for v in cc:
        if not used[v]:
            dv = 0
            for w in graph[v]:
                if not used[w]:
                    dv += 1

            if dv < deg:
                deg = dv
                u = v
            if deg < 2:
                break

    return u, deg

def solve(d):
    if d == 0:
        return 0

    v, deg = getlowdeg()
    if deg > 4:
        return 0

    branch_vertices = [v] if deg < 2 else graph[v]+[v] 

    ret = 0
    for u in branch_vertices:
        if used[u]:
            continue

        new_used = [w for w in [u]+graph[u] if not used[w]]
        for w in new_used:
            used[w] = True

        ret = max(ret, solve(d-1)+1)
        for w in new_used:
            used[w] = False

        if ret >= d:
            break 

    return ret

d = int(stdin.readline())
n = int(stdin.readline())

if d is 0 or n >= 5*d-4:
    print "possible"
    sys.exit()

graph = [[] for i in range(n)]

for i in range(n):
    s = stdin.readline().split()
    v = i
    
    for nbr in s[1:]:
        graph[v].append(int(nbr)-1)

used = n*[False]
searched = n*[False]
tot = 0
for v in range(n):
    if searched[v]:
        continue

    cc = []
    findcomponent(v)

    if len(cc) >= 6+4*(d-tot-2):
        tot = d
        break

    tot += solve(d-tot)
    if tot >= d:
        break

print ("possible" if tot >= d else "impossible")
