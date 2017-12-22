import random
import sys

n=100000

walk1 = [(0,0)]
walk2 = [(10000,10000)]

while len(walk1) < n and len(walk2) < n:
    if len(walk1) > n:
        sys.stderr.write('swap\n')
        (walk2, walk1) = (walk1, walk2)

    dx = 1 - walk1[-1][0]/5000
    dy = 1 - walk1[-1][1]/5000
    iters = 0
    while len(walk1) < n and (iters == 0 or
                              walk1[-1][0] not in [0, 10000] or
                              walk1[-1][1] not in [0, 10000]):
        iters += 1
        t = random.random()
        _dx = _dy = 0
        if t < 0.6:
            _dx = dx
        if t > 0.4:
            _dy = dy
        x = walk1[-1][0] + _dx
        y = walk1[-1][1] + _dy
        if x < 0 or x > 10000 or y < 0 or y > 10000:
            continue
        walk1.append((x,y))

        
    walk2.append((10000-walk2[-1][0],
                  10000-walk2[-1][1]))
    sys.stderr.write('%d %d (%d %d)\n' % (len(walk1), len(walk2), dx, dy))

(walk2, walk1) = (walk1, walk2)

print len(walk1)
for (x,y) in walk1:
    print '%d %d' % (x, y)
print len(walk2)
for (x,y) in walk2:
    print '%d %d' % (x, y)
    
