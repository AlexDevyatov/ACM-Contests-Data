import sys
import functools

n = int(sys.stdin.readline())
res = functools.reduce(lambda x, y: x * (4 * y - 2) // (y + 1), range(2, n + 2), 1)
print(res)
