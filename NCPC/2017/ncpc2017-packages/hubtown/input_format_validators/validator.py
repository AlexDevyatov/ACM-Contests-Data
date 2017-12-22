import re
import sys

INTEGER_REGEX = "(0|-?[1-9][0-9]*)?"

TWO_INTS = ' '.join([INTEGER_REGEX]*2) + "\\n"
THREE_INTS = ' '.join([INTEGER_REGEX]*3) + "\\n"

line = sys.stdin.readline()
assert re.match(TWO_INTS, line)
n, m = map(int, line.split())
assert 0 <= n <= 200000
assert 1 <= m <= 200000

for i in range(n):
    line = sys.stdin.readline()
    assert re.match(TWO_INTS, line)
    x, y = map(int, line.split())
    assert -1000 <= x <= 1000
    assert -1000 <= y <= 1000

trains = set()

def gcd(a, b):
    if not b: return a
    return gcd(b, a%b)

for i in range(m):
    line = sys.stdin.readline()
    assert re.match(THREE_INTS, line)
    x, y, c = map(int, line.split())
    assert x or y
    assert -1000 <= x <= 1000
    assert -1000 <= y <= 1000
    g = gcd(x, y)
    if g == 0: g = max(abs(x), abs(y))
    if g < 0: g = -g
    x /= g
    y /= g
    assert (x, y) not in trains
    trains.add((x, y))
    assert 0 <= c <= n


line = sys.stdin.readline()
assert len(line) == 0
sys.exit(42)
