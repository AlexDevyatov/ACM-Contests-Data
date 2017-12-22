import random

n=100000

walk1 = []
walk2 = []

x1 = random.randint(0, 10)
y1 = random.randint(0, 10)
x2 = 10000-random.randint(0, 10)
y2 = 10000-random.randint(0, 10)

print n
for i in range(n/2):
    print '%d %d' % (x1, y1)
    print '%d %d' % (x2, y2)
    

x1 = random.randint(0, 10)
y1 = 10000-random.randint(0, 10)
x2 = 10000-random.randint(0, 10)
y2 = random.randint(0, 10)

print n
for i in range(n/2):
    print '%d %d' % (x1, y1)
    print '%d %d' % (x2, y2)
