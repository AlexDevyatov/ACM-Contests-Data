import re
import sys

integer = "(0|[1-9]\d*)"
call_line = re.compile(integer + ' ' + integer + '( ' + integer + ')?\n')

line = sys.stdin.readline()

assert re.match(' '.join([integer]*4) + '\n', line)

(n, m, c1, c2) = map(int, line.split())

assert 4 <= n <= 250000 and n % 2 == 0, 'invalid n %d' % n
assert 1 <= m <= 500000, 'invalid m %d' % m
assert 1 <= c1 < c2 <= n, 'invalid c1 c2 %d %d' % (c1, c2)
assert c1 % 2 == 1 and c2 %2 == 1, 'invalid c1 c2 %d %d' % (c1, c2)

seen = set()
for i in range(m):
    line = sys.stdin.readline()
    assert call_line.match(line), 'call #%d/%d invalid line %s' % (i+1, m, line)
    vals = map(int, line.split())

    assert 1 <= vals[0] <= n
    assert 1 <= vals[1] <= n

    if len(vals) == 3:
        assert vals[0] % 2 != vals[1] % 2, 'not opposite sides in call line %s' % line
        assert vals[2] in [c1, c2], '%d is not a crossing in call line %s' % (vals[2], line)
    else:
        assert vals[0] % 2 == vals[1] % 2, 'opposite sides in call line %s' % line

    a = min(vals[0], vals[1])
    b = max(vals[0], vals[1])
    assert a != b
    assert (a,b) not in seen, 'call %s: endpoints already seen' % (line)
    seen.add((a,b))

assert sys.stdin.readline() == ''

sys.exit(42)

