from __future__ import print_function
from __future__ import division
try:
    import __builtin__
    input = getattr(__builtin__, 'raw_input', input)  # python 3 (pep 3111)
except:
    pass


N = int(input())
adj = []
for i in range(N):
    adj.append([int(x) for x in input().split(" ")][1:])

pred = [None for _ in range(N)]
visited = []

def find_match(n):
    if n is None:
        return True
    for to in adj[n]:
        if visited[to]:
            continue
        visited[to] = True
        if find_match(pred[to]):
            pred[to] = n
            return True
    return False


matching = 0
for i in range(N):
    visited = [False for _ in range(N)]
    if find_match(i):
        matching += 1

print(N - matching)
