from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


from collections import defaultdict
from heapq import heappop, heappush
import sys

max_dist = 2**60

N, M, K =   [int(x)   for x in input().split(' ')]
junc =      [int(x)-1 for x in input().split(' ')]
edges =    [[int(x)   for x in input().split(' ')] for _ in range(M)]

dist_old = [max_dist for _ in range(N)]
dist_new = [max_dist for _ in range(N)]
pred_old = [-1 for _ in range(N)]

for i in range(1, len(junc)):
    pred_old[junc[i]] = junc[i-1]

for edge in edges:
    edge[0] -= 1
    edge[1] -= 1
    if edge[0] > edge[1]:
        edge[0], edge[1] = edge[1], edge[0]
edges = list(sorted(edges))

adj = defaultdict(lambda : defaultdict(lambda : max_dist))
for a, b, c in edges:
    if pred_old[a] == b or pred_old[b] == a:
        if adj[a][b] == c:  # depends on normalized, sorted edges
            print('yes')
            sys.exit(0)
    adj[a][b] = min(adj[a][b], c)
    adj[b][a] = adj[a][b]

dist_old[0] = 0
for i in range(1, len(junc)):
    dist_old[junc[i]] = dist_old[junc[i-1]] + adj[junc[i-1]][junc[i]]


done = [False] * N
dist_new[0] = 0

todo = []
heappush(todo, (0, 0))
while len(todo):
    cur = heappop(todo)[1]
    if done[cur]: continue
    done[cur] = True
    for to, d in adj[cur].items():
        ndist = dist_new[cur] + d
        #print('{} -> {}, (d {}, nd {})'.format(cur, to, dist_new[to], ndist))
        if ndist == dist_old[to] and cur != pred_old[to]:
            print('yes')
            sys.exit(0)
        if ndist >= dist_new[to]: continue
        dist_new[to] = ndist
        heappush(todo, (ndist, to))

print('no')
