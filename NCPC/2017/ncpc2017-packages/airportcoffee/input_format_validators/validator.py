import re
import sys

INTEGER_REGEX = "(0|[1-9][0-9]*)?"

FIRST_LINE_REGEX = ' '.join([INTEGER_REGEX]*5) + "\\n"
SECOND_LINE_REGEX = INTEGER_REGEX + "\\n"
THIRD_LINE_REGEX = "(" + INTEGER_REGEX + "( " + INTEGER_REGEX + ")*)?"+ "\\n"

line = sys.stdin.readline()
assert re.match(FIRST_LINE_REGEX, line)
l, a, b, t, r = map(int, line.split())
assert 1 <= l <= 10**11
assert 1 <= a < b <= 200
assert 0 <= t <= 300
assert 1 <= r <= 1200

line = sys.stdin.readline()
assert re.match(SECOND_LINE_REGEX, line)
n = int(line)
assert 0 <= n <= 500000

line = sys.stdin.readline()
assert re.match(THIRD_LINE_REGEX, line)
dists = list(map(int, line.split()))
assert len(dists) == n
assert dists == sorted(dists)
assert len(set(dists)) == n
if dists:
    assert 0 <= dists[0] and dists[-1] <= l

line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
