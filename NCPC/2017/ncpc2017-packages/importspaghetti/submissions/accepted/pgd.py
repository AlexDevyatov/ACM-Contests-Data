#!/usr/bin/env pypy

from sys import stdin
from collections import deque

class Graph(object):
    def __init__(self, vertices):
        self.arcs = set()
        self.vertices = vertices
        self.neighbors = {v:set() for v in vertices}
    def add_arc(self, a,b):
        self.arcs.add((a,b))
        self.neighbors[a].add(b)

    def multiarc(self):
        for (a,b) in self.arcs:
            if (b,a) in self.arcs:
                return a,b

    def __len__(self):
        return len(self.vertices)

    def __getitem__(self, v):
        return self.neighbors[v]

    def __str__(self):
        return 'Graph(len=%d, arcs=%s)' % (len(self), str(self.arcs))

def cycle(g, v):
    """find cycle from v to v in graph G"""
    seen = set(g[v])
    queue = deque([(u, [u]) for u in g[v]])
    while queue:
        (vertex, path) = queue.popleft()
        for nxt in g[vertex]:
            if nxt == v:
                return path + [v]
            elif nxt not in seen:
                seen.add(nxt)
                queue.append((nxt, path + [nxt]))

def main(g):
    INF = 502
    m_arc = g.multiarc() # special case with a<->b
    if m_arc:
        return m_arc

    best = [0]*INF
    for v in g.vertices:
        path = cycle(g, v)
        if path is not None and len(path) < len(best):
            best = path
            if len(best) <= 3:
                return best # we already checked len 1 and 2
    if len(best) < INF:
        return best
    return None

def readgraph():
    v2i = {}
    i2v = {}
    n = int(stdin.readline())
    vs = stdin.readline().split()
    for i in range(n):
        v2i[vs[i]] = i
        i2v[i] = vs[i]
    g = Graph(list(range(n)))
    for i in range(n):
        name, lines = stdin.readline().split()
        v = v2i[name] # from vertex
        lines = int(lines)
        for j in range(lines):
            imp = stdin.readline().split()[1:]
            for elt in imp:
                u = v2i[elt.replace(',','')] # to vertex
                if v == u:
                    print('%s' % i2v[v]) # special case v<->v
                    exit(0)
                g.add_arc(v, u)
    return g, v2i, i2v

g, v2i, i2v = readgraph()
#print g
d = main(g)
if d is None:
    print('SHIP IT')
else:
    print(' '.join(map(lambda x: i2v[x], d)))
