from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


from collections import defaultdict
import re

def s2id_helper():
    return len(s2id)
s2id = defaultdict(s2id_helper)

N = int(input())
adj = [[] for _ in range(N)]
entry = []
visited = [False] * N

for i in range(N):
    method_str, _ = input().split(' ')
    callers = input().split(' ')
    if callers == ['']:
        callers = []

    method = s2id[method_str]
    callers = [s2id[c] for c in callers]

    if re.search('::PROGRAM$', method_str):
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

print(sum([1 for vis in visited if not vis]))
