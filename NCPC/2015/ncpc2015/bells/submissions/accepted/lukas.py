#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Solution by lukasP (Lukáš Poláček)
from sys import stdin

def gen(n):
    if n == 1:
        yield [1]
        return

    dir = False
    for enumer in gen(n - 1):
        o = list(enumer)
        if not dir:
            o.append(n)
        else:
            o.insert(0, n)
        yield o

        cur = 0 if dir else n - 1
        for i in range(n - 1):
            pos = cur + (1 if dir else -1)
            newo = list(o)

            newo[cur], newo[pos] = newo[pos], newo[cur]
            yield newo

            cur = pos
            o = newo
        dir = not dir

n = int(stdin.readline())
for row in gen(n):
    print(" ".join(map(str, row)))
