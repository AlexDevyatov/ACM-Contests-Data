import random
print(100000, 100000)
dat = []
for i in range(223):
    for j in range(223):
        dat.append((j + 2, 200))
    dat.append((1, 100))

additions = [[] for i in range(len(dat))]
for i in range(100000 - len(dat)):
    pos = random.randint(0, len(dat)-1)
    x = (random.randint(225, 100000), random.randint(1, 10))
    additions[pos].append(x)

for i in range(len(dat)):
    print(*dat[i])
    for a, b in additions[i]:
        print(a, b)
