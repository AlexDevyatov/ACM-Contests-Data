# Solution of problem Clock Pictures
# Time complexity: O(n*log(n))
# Author: Fredrik Svensson
import sys

n = int(sys.stdin.readline())
xAngles = sorted(map(int, sys.stdin.readline().split()))
yAngles = sorted(map(int, sys.stdin.readline().split()))
xDiffs = [xAngles[i]-xAngles[i-1] for i in range(n)]
xDiffs[0] = 360000+xAngles[0]-xAngles[-1]  # Avoid modulo on the line above
yDiffs = [yAngles[i]-yAngles[i-1] for i in range(n)]
yDiffs[0] = 360000+yAngles[0]-yAngles[-1]  # Avoid modulo on the line above

def matchPattern(needle, haystack):
    h = len(haystack)
    n = len(needle)
    prefix = [0]*(n+1)  # Lower index with same prefix pattern when matched a number of characters by now
    # Compute prefix
    prefix[0] = -1
    q = -1  # Number of characters matched
    for i in range(n):
        while q >= 0 and needle[q] != needle[i]:
            q = prefix[q]
        q += 1
        prefix[i+1] = q
    # Match
    q = 0;  # Number of characters matched
    for i in range(h):
        while q >= 0 and needle[q] != haystack[i]:
            q = prefix[q]
        q += 1
        if q == n:
            return True
    return False

# Find yDiffs in xDiffs+xDiffs
ret = matchPattern(yDiffs, xDiffs+xDiffs)
print(('' if ret else 'im') + 'possible')
