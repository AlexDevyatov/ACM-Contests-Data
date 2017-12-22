#!/usr/bin/env python
# -*- coding: utf-8
# greedy solution by pgd
# Takes minimum degree vertex

import sys
from sys import stdin

def solve(graph):
    used = set()
    
    delta = 1
    while delta != -1:
        delta = -1
        deg = len(graph)+2
        
        for i in range(len(graph)):
            if i not in used:
                canuse = True
                for x in graph[i]:
                    if x in used:
                        canuse = False
                if canuse:
                    if len(graph[i]) < deg:
                        delta = i
                        deg = len(graph[i])
        if delta != -1:
            used.add(delta)
    return len(used)

d = int(stdin.readline())
n = int(stdin.readline())

if d is 0 or n >= 5*d-4:
    print "possible"
    sys.exit()

graph = [[] for i in range(n)]

for i in range(n):
    s = stdin.readline().split()
    v = i # int(s[0]) (new format)
    
    for nbr in s[1:]:
        graph[v].append(int(nbr)-1)

print ("possible" if solve(graph) >= d else "impossible")
