import sys
import collections
import math
import bisect 

SIZE_TILES = 100


d = collections.defaultdict(list)
hits = 0
[goblins] = sys.stdin.readline().split()
goblins = int(goblins)

for i in range(goblins):
    [x,y]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    d[x] += [y]

for i in d:
    d[i].sort()

#print d
[missiles] = sys.stdin.readline().split()
missiles = int(missiles)
for m in range(missiles):
    [x, y, r]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    r = int(r)

    for i in range(-r, r+1):
        tmp = math.sqrt(r*r-i*i)

        #lower bound:
        l = bisect.bisect_left(d[x+i], y-tmp)

        #upper bound:
        u =  bisect.bisect_right(d[x+i], y+tmp)
        if l != u:
            hits +=(u-l)
            d[x+i]=d[x+i][0:l]+d[x+i][u:]
print (goblins - hits)
