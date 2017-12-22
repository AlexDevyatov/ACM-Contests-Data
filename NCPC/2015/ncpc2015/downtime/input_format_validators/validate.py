from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"

line = stdin.readline()
assert re.match(integer + " " + integer + "\n", line)
N, K = map(int,line.strip().split())
assert 1 <= N and N <= 100000
assert 1 <= K and K <= 100000

numbers = []

for i in xrange(N):
    line = stdin.readline()
    assert re.match(integer + "\n", line)
    ti = int(line)
    numbers.append(ti)
    assert 0 <= ti and ti <= 100000

assert sorted(numbers) == numbers

assert len(stdin.readline()) == 0
sys.exit(42)
