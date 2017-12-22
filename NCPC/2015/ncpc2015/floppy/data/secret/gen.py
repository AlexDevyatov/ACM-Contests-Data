from random import randint as r

F = r(1, 10)
print F
for _ in range(F):
    T = r(1, 10000)
    N = r(1, 100)
    print T, N,
    
    c = 0
    for _ in range(2 * N):
        c = c + r(1, int(T * 0.7))
        print c,
    print "\n",
