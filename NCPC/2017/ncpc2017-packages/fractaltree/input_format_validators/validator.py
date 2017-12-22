import re
import sys

INTEGER_REGEX = "(0|[1-9][0-9]*)?"

SINGLE_INT = INTEGER_REGEX + "\\n"
TWO_INT = ' '.join([INTEGER_REGEX]*2) + "\\n"
ANY_INT = "(" + INTEGER_REGEX + "( " + INTEGER_REGEX + ")*)?"+ "\\n"

line = sys.stdin.readline()
assert re.match(SINGLE_INT, line)
N = int(line)
assert 2 <= N <= 100000

line = sys.stdin.readline()
assert re.match(ANY_INT, line)
ps = list(map(int, line.split()))
assert len(ps) == N - 1

leaves = set(range(N))
for i in range(len(ps)):
    assert 0 <= ps[i] <= i
    if ps[i] in leaves: leaves.remove(ps[i])

line = sys.stdin.readline()
assert re.match(SINGLE_INT, line)
K = int(line)
assert 0 <= K < 2**30

nodes = N
leav = len(leaves)
if leav == 1:
    nodes = N + (N - 1) * K
else:
    for i in range(K):
        if nodes > 2**30: break
        nodes = nodes + leav * (N - 1)
        leav *= len(leaves)
mxNod = min(2**30, nodes)
print(mxNod)

line = sys.stdin.readline()
assert re.match(SINGLE_INT, line)
Q = int(line)
assert 1 <= Q <= 100000

for i in range(Q):
    line = sys.stdin.readline()
    assert re.match(TWO_INT, line)
    a, b = map(int, line.split())
    assert a != b
    assert 1 <= a <= mxNod
    assert 1 <= b <= mxNod

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
