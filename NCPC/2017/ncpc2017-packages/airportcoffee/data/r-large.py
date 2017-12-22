import random

L = 10000000
a = random.randint(1, 199)
b = random.randint(a+1, 200)
t = random.randint(0, 300)
r = random.randint(1, 1200)

n = random.randint(50000, 60000)

pos = sorted(random.sample(range(0, L+1), n))
print(L, a, b, t, r)
print(n)
print(*pos)
