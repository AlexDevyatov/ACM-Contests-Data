import random
print(2)
print(0)
print(1073741823)
print(100000)
for i in range(100000 - 3000 - 2):
    a, b = random.sample(range(1, 1073741824), 2)
    print(a, b)
for i in range(1000):
    a = random.choice(range(2, 1073741824))
    print(a, 1)
for i in range(1000):
    a = random.choice(range(1, 1073741824))
    print(1073741824, a)
for i in range(1000):
    a = random.choice(range(1, 1000))
    b = random.choice(range(1073741824-999, 1073741824))
    print(a, b)
print(1, 1073741824)
print(2, 1073741824)
