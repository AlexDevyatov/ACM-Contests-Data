# Solution of problem Catalan
# Time complexity: O(n)
# Author: Fredrik Svensson
import math
import sys

n = int(sys.stdin.readline())

c = [1 for i in range(n+1)]
for i in range(1,n+1):
    # f *= i
    # f2 *= (2*i-1)*(2*i)
    # c[i] = f2/((i+1)*f*f) =
    #       c[i-1]*(i/(i+1))*(2*i-1)*(2*i)/(i*i) = 
    #       c[i-1]*(2*i-1)*2/(i+1)
    c[i] = c[i-1]*(2*i-1)*2/(i+1)
sn = sum(c[i]*c[n-i] for i in range(n+1))
print(sn)
sys.exit(0)
