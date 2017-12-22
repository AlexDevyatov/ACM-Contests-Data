#!/usr/bin/env python
# -*- coding: utf-8
#Solution by Markus & Pal

from sys import stdin

s = stdin.readline().split()
n, k = int(s[0]), int(s[1])

a = []
for i in range(n):
        q = tuple(map(int, stdin.readline().split()))
        a.append(q)

a = sorted(a, key=lambda x: x[0])

q = []
sol = 0

for i in range(k):
	sol += 1
	q.append(a[i])

for i in range(k, n):
	f = q[0]

        for x in q:
                if f[1] > x[1]:
                        f = x
            
        c = a[i]
	if f[1] <= c[0]:
		q.remove(f)
		q.append(c)
		sol += 1

print sol
