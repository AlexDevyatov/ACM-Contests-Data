from os import system
from random import randint

for x in range(1,9+1):
    q = 10**4
    n = [   1,   1,1000, 300, 700,1000,1000,1000,1000][x-1]
    m = [   1,1000,   1, 700, 300,1000,1000,1000,1000][x-1]
    r = [   1,1000,   1, 100, 100,   1,  10, 100,1000][x-1]
    f = open("secret/" + str(x) + ".in", "w")
    f.write(str(n) + " " + str(m) + " " + str(q) + "\n")
    for i in range(q):
        if randint(1,2) == 1:
            y1 = y2 = randint(1,n)
            x1 = randint(1,m)
            x2 = randint(x1,min(x1+r-1,m))
        else:
            x1 = x2 = randint(1,m)
            y1 = randint(1,n)
            y2 = randint(y1,min(y1+r-1,n))
        f.write(str(y1) + " " + str(x1) + " " + str(y2) + " " + str(x2) + "\n")
    f.close()
    system("../submissions/accepted/antti_dsu < secret/" + str(x) + ".in > secret/" + str(x) + ".ans")
    print "ok",x
