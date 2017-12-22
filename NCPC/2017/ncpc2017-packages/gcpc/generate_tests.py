from random import randint, seed
from os import system

seed(181846081)

for x in range(12):
    n = 10**5
    m = 10**5
    data = []
    if x < 6:
        r = 1
    else:
        r = 1000
    if x%6 == 0:
        for i in range(m):
            data.append((1,randint(1,r)))
    if x%6 == 1:
        for i in range(m):
            data.append((2,randint(1,r)))
    if x%6 == 2:
        for i in range(m):
            data.append((randint(1,5),randint(1,r)))
    if x%6 == 3:
        for i in range(m):
            data.append((randint(1,n),randint(1,r)))
    if x%6 == 4:
        for i in range(m):
            if randint(1,2) == 1:
                data.append((1,randint(1,r)))
            else:
                data.append((randint(2,n),randint(1,r)))
    if x%6 == 5:
        for i in range(m):
            if randint(1,100) == 1:
                data.append((randint(6,n),randint(1,r)))
            else:
                data.append((randint(1,5),randint(1,r)))
    f = open("data/secret/" + str(x+1) + ".in", "w")
    f.write(str(n) + " " + str(m) + "\n")
    for d in data:
        f.write(str(d[0]) + " " + str(d[1]) + "\n")
    f.close()
    system("submissions/accepted/antti_fast < data/secret/" + str(x+1) + ".in > data/secret/" + str(x+1) + ".ans")
    print "test case", x+1, "created"
