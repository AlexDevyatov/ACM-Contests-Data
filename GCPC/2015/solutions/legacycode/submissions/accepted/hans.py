from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


from collections import defaultdict
import re

N = int(input())
adj = defaultdict(list)
entry = []
visited = {}

for i in range(N):
    method, _ = input().split(' ')
    callers = input().split(' ')
    if callers == ['']:
        callers = []

    visited[method] = False
    if re.search('::PROGRAM$', method):
        entry.append(method)

    for caller in callers:
        adj[caller].append(method)

todo = entry[:]
while len(todo) > 0:
    cur = todo.pop(0)
    visited[cur] = True
    for to in adj[cur]:
        if not visited[to]:
            visited[to] = True
            todo.append(to)

print(sum([1 for vis in visited.values() if not vis]))
