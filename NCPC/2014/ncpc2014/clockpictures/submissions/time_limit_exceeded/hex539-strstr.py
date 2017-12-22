#!/usr/bin/env python

#
# Author
#   Robin Lee (hex539)
#
# Algorithm
#   Convert each clock to a string representation. If they both convert to
#   the same cyclic string then the clocks are identical. We do this by
#   first checking the lengths are the same then seeing if one string is
#   a substring of the other when it is repeated twice.
#
#   Sadly, Python's "in" operator is not efficient so this times out
#
# Complexity
#   O(N^2)
#

from sys import stdin

def read_clock(n):
    v = sorted(map(int, stdin.readline().split()))
    v = [v[i+1] - v[i] for i in range(n-1)] + [v[0] - v[-1] + 360000]
    return ','.join(map(str, v)) + ','

n = int(stdin.readline())
a = read_clock(n)
b = read_clock(n)

if len(a) == len(b) and a in (b+b):
    print 'possible'
else:
    print 'impossible'
