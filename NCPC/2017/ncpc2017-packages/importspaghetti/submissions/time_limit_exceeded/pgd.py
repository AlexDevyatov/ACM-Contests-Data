#
# The complexity is ~m^2 ~ n^4 and should time out, whereas the n^3 should work.
#
# The algorithm is: minimize over: for each arc e=(v,u), remove e from graph and
# compute distance from u to v.  If v is reachable from u, then there is a
# cycle.
#

from sys import stdin
from collections import deque

class Graph(object):
    def __init__(self, vertices):
        self.arcs = set()
        self.vertices = vertices
    def add_arc(self, a,b):
        self.arcs.add((a,b))

    def multiarc(self):
        for (a,b) in self.arcs:
            if (b,a) in self.arcs:
                return a,b

    def __len__(self):
        return len(self.vertices)

    def neighbors(self, v):
        ns = []
        for e in self.arcs:
            if e[0] == v:
                ns.append(e[1])
        return ns

    def __getitem__(self, v):
        return set(self.neighbors(v))

    def without(self, e):
        g = Graph(self.vertices)
        for f in self.arcs:
            if f != e:
                g.add_arc(f[0],f[1])
        return g
    def __str__(self):
        return 'Graph(len=%d, arcs=%s)' % (len(self), str(self.arcs))

def shortest(g, v, u):
    queue = deque([(w, [w]) for w in g[v]])
    seen = set(g[v])
    while queue:
        (vertex, path) = queue.pop()
        for nxt in g[vertex] - seen:
            if nxt == u:
                return [v] + path + [u]
            else:
                seen.add(nxt)
                queue.append((nxt, path + [nxt]))

def main(g):
    m_arc = g.multiarc() # special case with a<->b
    if m_arc:
        return m_arc

    sd = None
    for e in g.arcs:
        h = g.without(e)
        v1,v2 = e
        d = shortest(h, v2, v1)
        if d is not None:
            if sd is None or len(d) < len(sd):
                sd = d
    return sd

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
                    print(i2v[v])
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
