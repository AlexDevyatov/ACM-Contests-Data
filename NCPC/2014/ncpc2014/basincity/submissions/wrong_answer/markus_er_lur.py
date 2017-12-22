#!/usr/bin/env python3
# -*- coding: utf-8

# Solution by Markus (through the eyes of Paal)

import sys,time
from sys import stdin

current_milli_time = lambda: int(round(time.time() * 1000))

NOW = current_milli_time()

def solve(v, d):

    # markus is tricky clever
    global NOW
    but_now = current_milli_time()
    if but_now - NOW > 1500:
        print("impossible")
        exit(0)

    if d is 0:
        return True

    while v < n and used[v]:
        v = v + 1
    
    if v is n:
        return False 

    for u in [v] + graph[v]:
        if used[u]:
            continue

        new_used = [x for x in [u] + graph[u] if not used[x]]
        for w in new_used:
            used[w] = True

        res = solve(v+1, d-1)
        
        for w in new_used:
            used[w] = False

        if res:
            return True

    return False

d = int(stdin.readline())
n = int(stdin.readline())

if d is 0 or n >= 5*d-4:
    print("possible")
    sys.exit()

graph = [[] for i in range(n)]
used = [False]*n

for i in range(n):
    s = stdin.readline().split()
    v = i
    
    for nbr in s[1:]:
        graph[v].append(int(nbr)-1)

print("possible" if solve(0, d) else "impossible")
