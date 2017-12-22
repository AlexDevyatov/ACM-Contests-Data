import sys
import collections
import math

SIZE_TILES = 100


d = collections.defaultdict(lambda:collections.defaultdict(int))
hits = 0
[gremlins] = sys.stdin.readline().split()
gremlins = int(gremlins)

for i in range(gremlins):
    [x,y]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    d[x][y]+=1

#print d
[missiles] = sys.stdin.readline().split()
missiles = int(missiles)
for m in range(missiles):
    [x, y, r]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    r = int(r)

    for i in range(-r, r+1):
        tmp = int(math.floor(math.sqrt(r*r-i*i)))
#        print tmp
        for j in range(-tmp, tmp+1):
#            print i, j
            hits += d[x+i][y+j]
            del(d[x+i][y+j])
print (gremlins - hits)
