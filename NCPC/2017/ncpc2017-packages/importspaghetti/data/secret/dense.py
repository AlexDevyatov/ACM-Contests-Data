#!/usr/bin/env pypy
from random import random as rd, randint as rnd
import sys
from time import time as t

INF=500

def ok(e, edges, n):
    # false if ba
    # or E i s.t. bia
    # or E i,j s.t. bija
    a,b=e
    if (b,a) in edges:
        return False
    for i in range(n):
        if (b,i) not in edges:
            continue
        if (b,i) in edges and (i,a) in edges:
            return False
        for j in range(n):
            if (j,a) in edges and (i,j) in edges:
                return False
    return True

def gengraph(n, density):
    if n > INF:
        exit('n = %d > %d' % (n, INF))
    def rnd_name():
        return ''.join([chr(rnd(97,97+25)) for i in range(8)])

    vertices = [rnd_name() for _ in range(n)]
    edges = set()


    for i in range(n):
        for j in range(n):
            if i != j and rd() < density:
                if ok((i,j), edges, n):
                    edges.add((i,j))
    return vertices, edges


def main(n, density):
    vertices, edges = gengraph(n, density)
    with open('gen%d.%d.in' % (n, int(density*10)), 'w') as f:
        f.write('%d\n' % n)
        f.write(' '.join(vertices))
        f.write('\n')
        outarc = lambda x: vertices[x[1]]
        for i in range(n):
            arcs = [(i, j) for j in range(n) if (i,j) in edges]
            if arcs:
                f.write('%s 1\n' % vertices[i])
                f.write('import %s' % ', '.join(map(outarc, arcs)))
            else:
                f.write('%s 0' % vertices[i])
            f.write('\n')

if __name__ == '__main__':
    start, stop, step = map(int, sys.argv[1:4])
    density = float(sys.argv[4])
    for i in range(start, stop+1, step):
        t1 = t()
        main(i, density)
        t2 = t()
        print('%d\t%.3d s' % (i, int(t2-t1)))
