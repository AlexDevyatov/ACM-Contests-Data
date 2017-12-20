from __future__ import print_function
import __builtin__
input = getattr(__builtin__, 'raw_input', input)  # as in Python 3 (PEP 3111)


import itertools

N = int(input())
A = [int(x) for x in input().split(' ')]

# extremely literal
# extremely pointless
indices = itertools.product(range(N), range(N))
X = [A[j] - A[i] if i < j else 9001 for i, j in indices]
extreme_property = min(X) >= 0

print("yes" if extreme_property else "no")
