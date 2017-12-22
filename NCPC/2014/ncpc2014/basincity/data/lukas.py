import random


def add(g, a, b, p):
    g[p[a]].append(p[b])
    g[p[b]].append(p[a])

copies = 14
clique = 5
g = [[] for x in range(copies * clique)]
a = list(range(len(g)))
# random.shuffle(a)

for i in range(copies):
    base = i * clique
    for j in range(clique):
        for k in range(j):
            if i == 0 and j == clique - 1 and k == clique - 2:
                continue
            add(g, base + k, base + j, a)

print(copies + 1)
print(len(g))
for x in g:
    print(" ".join(map(str, [len(x)] + [y + 1 for y in x])))
