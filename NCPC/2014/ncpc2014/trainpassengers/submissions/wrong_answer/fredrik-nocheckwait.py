# Solution of problem Train Passangers
# Time complexity: O(n)
# Author: Fredrik Svensson
import sys

def doit():
    (capacity, n) = map(int, sys.stdin.readline().split())
    ontrain = 0
    for i in range(n):
        (left, entered, stayed) = map(int, sys.stdin.readline().split())
        ontrain -= left
        if ontrain < 0:
            return False
        ontrain += entered
        if ontrain > capacity:
            return False
    return ontrain == 0

ret = doit()
print(('' if ret else 'im') + 'possible')
