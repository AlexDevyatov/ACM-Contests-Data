import random

n=100000

walk1 = []
walk2 = []

for i in range(n-1):
    x = random.randint(0, 5000)
    y = random.randint(5000, 10000)
    walk1.append((x, y))

walk1.append((10000, 5000))

for (x, y) in walk1[:-1]:
#    walk2.append((x+5000, y-5000))
    walk2.append((15000-y, x))

walk2.append((10000, 10000))
joins = 0
    
for i in range(joins):
    x = walk1[-i-1][0]
    y = walk1[-i-1][0]

    while True:
        x1 = x + random.randint(-2, 2)
        y1 = y + random.randint(-2, 2)
        if (0 <= x1 <= 10000 and 0 <= y1 <= 10000 and
            (x1 != x or y1 != y)):
            break
    walk2.append((x1, y1))

print n
for (x,y) in walk1:
    print '%d %d' % (x, y)
print n
for (x,y) in walk2:
    print '%d %d' % (x, y)
    
