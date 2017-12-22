import sys
import collections
import math
import copy

d = []
hits = 0

[gremlins] = sys.stdin.readline().split()
gremlins = int(gremlins)

for i in range(gremlins):
    [x,y]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    d += [(x,y)]

[missiles] = sys.stdin.readline().split()
missiles = int(missiles)
for i in range(missiles):
    [x,y,r]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    r = int(r)
    for(x_g,y_g) in copy.copy(d):
        if (math.hypot(x_g - x, y_g - y)<=r):
            hits +=1
            d.remove((x_g,y_g))
print (gremlins - hits)
