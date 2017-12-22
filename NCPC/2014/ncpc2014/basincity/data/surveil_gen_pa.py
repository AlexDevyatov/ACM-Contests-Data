import random
import sys

case_no = 1
K_max = 15
K_5 = [(1,2),(1,3),(1,4),(1,5), (2,3), (2,4), (2,5), (3,4), (3,5), (4,5)]
K_4 = [(a,b) for (a,b) in K_5 if b <= 4]

prefixes = ["rr", "rn", "nr", "nn", "s1", "s2"]

def write_test(k, n, edges):
    global case_no

    for typ in range(6):
        f = open('per.%d.%s.in' % (case_no, prefixes[typ]), 'w')
        neighs = [[b for (a,b) in edges if a == i] + [a for (a,b) in edges if b == i] for i in range(1, n+1)]
        f.write('%d\n%d\n' % (k, n))

        a = range(len(neighs))
        if typ < 4 and typ // 2 == 0:
            a = list(reversed(a))
        if typ >= 4:
            random.shuffle(a)

        nN = [[] for x in range(n)]
        for i in range(n):
            nN[a[i]] = neighs[i]
        neighs = nN

        for N in neighs:
            if typ % 2 == 0 and typ < 4:
                N = list(reversed(N))
            if typ >= 4:
                random.shuffle(N)
            nN = range(len(N))
            for i, x in enumerate(N):
                nN[i] = a[x - 1] + 1
            N = nN
            f.write('%s\n' % ' '.join(map(str, [len(N)]+N)))
        f.close()
    case_no +=1


K_6 = [(i,j) for i in range(6) for j in range(i)]


def disjoint_sum(graphs):
    res = []
    N = 0
    for G in graphs:
        res = res + [(a+N,b+N) for (a,b) in G]
        n = max([max(e) for e in G])
        N += n
    return res

def cycle(len):
    return [(i+1, (i+1)%len+1) for i in range(len)]

# 5 vertices, unique IS of size 2 (K_5 minus one edge)
def unique_size_2():
    return K_5[:-1]

# 8 vertices, unique IS of size 3 -- is 9 vertices impossible?
# if 9 vertices was possible would maybe give worst constr.
def unique_size_3():
    edges = cycle(5)
    edges = edges + [(6, i) for i in range(1,5)] + [(7,i) for i in range(3,6)] + [(8,i) for i in [5,1,2]]
    return edges

# 15 vertices, unique IS of size 5
def unique_size_5():
    edges = disjoint_sum([cycle(3),cycle(3),cycle(4)])
    edges = edges + [(11,i) for i in range(1,4)]
    edges = edges + [(12,i) for i in range(1,4)]
    edges = edges + [(13,i) for i in range(4,7)]
    edges = edges + [(14,i) for i in range(4,7)]
    edges = edges + [(15,i) for i in range(7,11)]
    edges = edges + [(11+i,7+i) for i in range(4)]
    return edges

# 18 vertices, unique IS of size 6
def unique_size_6():
    edges = []
    for i in range(4):
        for j in range(3):
            edges.append((3*i+j+1, 3*i+(j+1)%3+1))

    cross =  [(0,1),(0,1),(0,1),(2,3),(2,3),(2,3),(4,5),(4,5),(4,5),(0,3),(1,4),(2,5)]
    for i in range(12):
        edges.append((13+cross[i][0], i+1))
        edges.append((13+cross[i][1], i+1))
    return edges

# 45 vertices, unique IS of size 15 (I hope)
# connected as opposed to taking disjoint sum of "unique_size_5"
def unique_size_15():
    edges = disjoint_sum([cycle(3)]*10)
    for i in range(7):
        edges = edges + [(31+i, 1+3*i+j) for j in range(3)]
        edges = edges + [(31+i+7, 1+3*i+j) for j in range(3)]
    # tri-vertices 22..30 remain
    edges = edges + [(31+i, 22+i) for i in range(5)]
    edges = edges + [(36+i, 22+i) for i in range(5)]
    # tri-vertices 27,28,29,30 remain
    edges = edges + [(41+i, 27+i) for i in range(4)]
    edges = edges + [(45, 27+i) for i in range(4)]
    return edges


write_test(K_max, (K_max-1)*5, disjoint_sum([K_5 for i in range(K_max)]))
write_test(14, 18+18+5, disjoint_sum([unique_size_6(), unique_size_6(), unique_size_2()]))
write_test(15, 18+18+8, disjoint_sum([unique_size_6(), unique_size_6(), unique_size_3()]))
write_test(15, 15*3, disjoint_sum([unique_size_5()]*3))
write_test(15, 45, unique_size_15())
sys.exit(0)

while True:
    pairs = match_up3_random()
    if pairs is not None:
        print pairs
        sys.exit(0)



