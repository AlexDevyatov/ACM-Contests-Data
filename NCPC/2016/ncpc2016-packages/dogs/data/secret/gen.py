import random

n=100000

walk1 = []
walk2 = []

for i in range(n):
    x = random.randint(0, 10000)
    y = random.randint(0, 10000)

    while True:
        x1 = x + random.randint(-2, 2)
        y1 = y + random.randint(-2, 2)
        x2 = x + random.randint(-2, 2)
        y2 = y + random.randint(-2, 2)
        if (0 <= x1 <= 10000 and 0 <= y1 <= 10000 and
            0 <= x2 <= 10000 and 0 <= y2 <= 10000 and
            (x1 != x2 or y1 != y2)):
            break
    walk1.append((x1,y1))
    walk2.append((x2,y2))

print n
for (x,y) in walk1:
    print '%d %d' % (x, y)
print n
for (x,y) in walk2:
    print '%d %d' % (x, y)
    
