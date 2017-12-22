from random import randint, seed
from os import system

seed(586254551)

data = []
for a in [1,2,100,1000,10**5]:
    for b in [1,2,5,20]:
        data.append((a,b))

x = 0
for z in data:
    n = int(z[0])
    k = int(z[1])
    f = open("data/secret/" + str(x+1) + ".in", "w")
    f.write(str(n) + " " + str(k) + "\n")
    for d in range(n):
        u = ""
        for i in range(k):
            u += "01"[randint(0,1)]
        f.write(u + "\n")
    f.close()
    system("submissions/accepted/antti_bfs < data/secret/" + str(x+1) + ".in > data/secret/" + str(x+1) + ".ans")
    print "test case", x+1, "created"
    x += 1
