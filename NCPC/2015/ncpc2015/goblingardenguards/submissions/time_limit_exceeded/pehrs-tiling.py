import sys
import collections
import math

SIZE_TILES = 100


d = collections.defaultdict(lambda:collections.defaultdict(lambda:collections.defaultdict(int)))
hits = 0
[gremlins] = sys.stdin.readline().split()
gremlins = int(gremlins)

for i in range(gremlins):
    [x,y]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    d[x/SIZE_TILES][y/SIZE_TILES][(x,y)]+=1

#print d
[missiles] = sys.stdin.readline().split()
missiles = int(missiles)
for i in range(missiles):
    [x, y, r]= sys.stdin.readline().split()
    x = int(x)
    y = int(y)
    r = int(r)
    candidates = []
    for i in [-1, 0, 1]:
        for j in [-1, 0, 1]:
              candidates += d[(x/SIZE_TILES)+i][(y/SIZE_TILES)+j].keys()
#              print (x/NUM_TILES)+i, (y/NUM_TILES)+j, d[(x/NUM_TILES)+i][(y/NUM_TILES)+j].keys()
    for(x_g,y_g) in candidates:
         if (math.hypot(x_g - x, y_g - y)<=r):
             hits += d[(x_g/SIZE_TILES)][(y_g/SIZE_TILES)][(x_g,y_g)]
             del d[x_g/SIZE_TILES][y_g/SIZE_TILES][(x_g,y_g)]

print (gremlins - hits)
