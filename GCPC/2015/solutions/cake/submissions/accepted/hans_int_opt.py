from __future__ import print_function
try:
    import __builtin__
    input = getattr(__builtin__, 'raw_input', input)  # Python 3 (PEP 3111)
except:
    pass


from math import *

a, N = input().split(" ")
a, N = float(a), int(N)

point = [input().split(" ") for _ in range(N)]
point = [(int(x), int(y)) for x, y in point]
point += point[0:2]

area_twice = 0
for i in range(1, N+1):
    pa, pb = point[i-1], point[i]
    area_twice += pa[0] * pb[1] - pa[1] * pb[0]
area_twice = abs(area_twice)

cut_twice = 0
for j in range(1, N+1):
    i, k = j-1, j+1
    pa = (point[i][0] - point[j][0], point[i][1] - point[j][1])
    pb = (point[k][0] - point[j][0], point[k][1] - point[j][1])
    cut_twice += abs(pa[0] * pb[1] - pa[1] * pb[0])

# A - sum(cut) / s**2 = a * A
s = sqrt(cut_twice / (area_twice * (1.0 - a)))
print(s)
