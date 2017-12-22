import random
random.seed(1324)
print(10)
print(*[random.randint(0, i) for i in range(9)])
print(10)
print(100000)
MX = 653034700
for i in range(100000 - 5000):
    a, b = random.sample(range(1, MX), 2)
    print(a, b)
for i in range(1000):
    a = random.choice(range(2, MX))
    print(a, 1)
for i in range(1000):
    a = random.choice(range(1, MX))
    print(MX, a)
for i in range(1000):
    a = random.choice(range(1, 1000))
    b = random.choice(range(MX-999, MX))
    print(a, b)
for i in range(2000):
    a = random.choice(range(1, MX-10))
    b = random.choice(range(a+1, a+10))
    print(a, b)
