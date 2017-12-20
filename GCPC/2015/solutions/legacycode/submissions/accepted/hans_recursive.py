from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


from collections import defaultdict
import re
import sys
sys.setrecursionlimit(5000)

def s2id_helper():
    return len(s2id)
s2id = defaultdict(s2id_helper)

N = int(input())
starter = [False] * N
adj = [[] for _ in range(N)]

for i in range(N):
    method_str, _ = input().split(' ')
    callers = input().split(' ')
    if callers == ['']:
        callers = []

    method = s2id[method_str]
    callers = [s2id[c] for c in callers]

    adj[method] = callers
    if re.search('::PROGRAM$', method_str):
        starter[method] = True

def needed(method):
    if starter[method]:
        return True

    seen[method] = True
    for m in adj[method]:
        if not seen[m]:
            seen[m] = True
            if needed(m):
                return True
    return False

result = 0
for m in range(N):
    seen = [False] * N
    if not needed(m):
        result += 1

print(result)
