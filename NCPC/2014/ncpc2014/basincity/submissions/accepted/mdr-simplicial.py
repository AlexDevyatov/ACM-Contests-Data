# Solution by Markus Dregi
# Same algorithm as mdr-simplicial-fast.cpp
# Complexity: 3^k n

import sys
from sys import stdin

# Finds a good vertex to branch on. Either a simplicial vertex or a low-degree
def search():
    bv = -10
    min_deg = 10
    for v in range(n):
        if used[v]:
            continue
        s = True
        d = 0
        for i in range(len(graph[v])):
            n1 = graph[v][i]
            if used[n1]:
                continue
            d += 1
            for n2 in graph[v][i+1:]:
                if not s:
                    break
                if not used[n2] and not adjacent[n1][n2]:
                    s = False
        if s:
            return True, v
        elif d < min_deg:
            bv = v
            min_deg = d
    return False, bv

# Adds all vertices in branch_vertices to the independent set and 
# recurses for a solution of size target.
def branch(branch_vertices, target):
    new_used = []
    for u in branch_vertices:
        for v in graph[u]:
            if not used[v]:
                new_used.append(v)

    # Update
    for v in new_used+branch_vertices:
        used[v] = True

    # Recurse
    size = len(branch_vertices)
    size += solve(target-size)

    # Reset
    for v in new_used+ branch_vertices:
        used[v] = False

    return size

# Searches for a solution of size target
def solve(target):
    if target <= 0:
        return 0

    simplicial, bv = search()
    if bv < 0:
        return 0

    best = branch([bv], target)
    if not simplicial:
        for i in range(len(graph[bv])):
            u = graph[bv][i]
            if used[u]:
                continue
            for v in graph[bv][i+1:]:
                if not used[v] and not adjacent[u][v]:
                    best = max(best, branch([u,v], target))
                    if best >= target:
                        return best

    return best

d = int(stdin.readline())
n = int(stdin.readline())

if d is 0 or n >= 5*d-4:
    print "possible"
    sys.exit()

graph = [[] for i in range(n)]
adjacent = [[False for i in range(n)] for j in range(n)]
used = [False]*n

for i in range(n):
    s = stdin.readline().split()
    for nbr in s[1:]:
        graph[i].append(int(nbr)-1)
        adjacent[i][int(nbr)-1] = True

print ("possible" if solve(d) >= d else "impossible")
