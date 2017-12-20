from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


from heapq import heappop, heappush
from collections import defaultdict
import sys


def get_int_line():
    return [int(x) for x in input().split(' ')]

max_dist = 2**60

N, P, M, G, T = get_int_line()
sites = [get_int_line() for _ in range(P)]
edges = [get_int_line() for _ in range(M)]

# site cost
G -= sum([s[1] for s in sites])

# ensure 0 (athens) is in sites and is first item
sites = [s[0] for s in sites if s[0] != 0]
sites = [0] + sites
P = len(sites)

if sites == [0]:
    if G >= 0:
        print('possible without taxi')
    else:
        print('impossible')
    sys.exit(0)


adj = defaultdict(lambda : defaultdict(lambda : max_dist))
for s, d, t in edges:
    adj[s][d] = min(adj[s][d], t)
    adj[d][s] = adj[s][d]

for k in adj.keys():
    adj[k] = adj[k].items()

sites_adj = [[max_dist] * P for _ in range(P)]

# P times dijkstra
for s, start in enumerate(sites):
    if s == 0:
        continue
    done = [False] * N
    dist = [max_dist] * N
    dist[start] = 0

    todo = []
    heappush(todo, (0, start))
    while len(todo):
        cur = heappop(todo)[1]
        if done[cur]: continue
        done[cur] = True
        for to, d in adj[cur]:
            ndist = dist[cur] + d
            if ndist >= dist[to]: continue
            dist[to] = ndist
            heappush(todo, (ndist, to))
    for o, other in enumerate(sites):
        if o < s:
            sites_adj[o][s] = dist[other]
            sites_adj[s][o] = dist[other]

# TSP
row = [max_dist for _ in range(P)]
notaxi   = [row[:] for _ in range(1<<P)]
withtaxi = [row[:] for _ in range(1<<P)]

for x in range(0, P):
    notaxi[1<<x][x] = sites_adj[0][x]
    withtaxi[1<<x][x] = T

order = []
for i in range(1<<P):
    order.append((bin(i).count("1"), i))
order = [x[1] for x in sorted(order)]

for bm in order:
    bits = [0] if bm == (1<<P) - 2 else range(1, P)
    for x in bits:
        if bm & (1<<x): continue
        nbm = (bm | (1<<x))

        for b, dist in enumerate(notaxi[bm]):
            if dist >= max_dist: continue
            notaxi[nbm][x] = min(notaxi[nbm][x], dist + sites_adj[b][x])
            withtaxi[nbm][x] = min(withtaxi[nbm][x], dist + T)

        for b, dist in enumerate(withtaxi[bm]):
            if dist >= max_dist: continue
            withtaxi[nbm][x] = min(withtaxi[nbm][x], dist + sites_adj[b][x])

bm = (1<<P) - 1
nt, wt = min(notaxi[bm]), min(withtaxi[bm])

if nt <= G:
    print('possible without taxi')
elif wt <= G:
    print('possible with taxi')
else:
    print('impossible')
