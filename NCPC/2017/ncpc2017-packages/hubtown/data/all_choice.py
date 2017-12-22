import random

def gcd(a, b):
    if not b: return abs(a)
    return gcd(b, a%b)

print(199992, 100000 + 2)
for i in range(641):
    for j in range(199992//641):
        print(0,j+1)
print(1, 0, 199992//2 - 1)
print(-1, 0, 199992//2 - 1)
w = set()
for i in range(100000):
    x, y = random.randint(-800, 800), random.randint(-800, -1)
    g = gcd(x, y)
    x //= g
    y //= g
    while (x, y) in w:
        x, y = random.randint(-800, 800), random.randint(-800, -1)
        g = gcd(x, y)
        x //= g
        y //= g
    w.add((x, y))
for x, y in w:
    print(x, y, 199992)
