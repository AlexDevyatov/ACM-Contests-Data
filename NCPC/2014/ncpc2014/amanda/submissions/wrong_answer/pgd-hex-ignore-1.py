#!/usr/bin/env python3
#
# Author
# This is PGD messin up the algorithm of Robin Lee (hex539)

import sys
import collections
q = collections.deque()

class Airport:
  def __init__(self, name):
    self.visited = False
    self.colour = None
    self.edges = []

  def paint(self, colour):
    if self.colour is not None and self.colour is not colour:
      print('impossible')
      sys.exit(0)
    self.colour = colour

  def solve(self):
    self.visited = True
    soln = [0,0]
    q.append(self)
    while len(q) != 0:
      x = q.pop()
      soln[int(x.colour)] += 1
      for i in x.edges:
        i.paint(not x.colour)
        if not i.visited:
          i.visited = True
          q.append(i)
    return soln

data = list(map(int, sys.stdin.read().split()))
n,m = data[0:2]
v = list(map(Airport, range(n)))

for i in range(m):
  a,b,c = data[2+3*i:5+3*i]
  a = a-1
  b = b-1
  c = 1
  for i in (a,b):
    if c == 1:
      v[i].edges += [v[a+b-i]]
    else:
      v[i].paint(c == 2)

res = 0
for i in v:
  if not i.visited and i.colour is not None:
    res += i.solve()[1]
for i in v:
  if not i.visited:
    i.paint(True)
    res += min(i.solve())
print(res)
