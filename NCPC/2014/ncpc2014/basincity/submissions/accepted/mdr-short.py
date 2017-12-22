from sys import *

def branch(bv, branch_vertices, target):
    new_used = [v for u in branch_vertices for v in graph[u] if not used[v]]
    for v in new_used+branch_vertices:
        used[v] = True
    size = solve(bv, target-len(branch_vertices)) + len(branch_vertices)
    for v in new_used+ branch_vertices:
        used[v] = False
    return size

def solve(bv, target):
    if target <= 0 or bv >= n:
        return 0
    if used[bv]:
        return solve(bv+1, target)
    best = branch(bv+1, [bv], target)
    for i in range(len(graph[bv])):
        if not used[graph[bv][i]]:
            for v in graph[bv][i+1:]:
                if not used[v] and not adjacent[graph[bv][i]][v]:
                    best = max(best, branch(bv+1, [graph[bv][i],v], target))
                    if best >= target:
                        return best
    return best

d, n = int(stdin.readline()), int(stdin.readline())
if d is 0 or n >= 5*d-4:
    print "possible"
    exit()
graph = [[] for i in range(n)]
adjacent = [[False for i in range(n)] for j in range(n)]
used = [False]*n
for i in range(n):
    s = stdin.readline().split()
    for nbr in s[1:]:
        graph[i].append(int(nbr)-1)
        adjacent[i][int(nbr)-1] = True
print ("possible" if solve(0, d) >= d else "impossible")
