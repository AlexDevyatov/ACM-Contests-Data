import sys
def main():
    typ = []
    cost = []
    fac = []
		
    tab = [[0 for y in xrange(10101)] for x in xrange(110)]
		
    g, c, n = [int(x) for x in sys.stdin.readline().split()]
    for i in xrange(n):
        inp = sys.stdin.readline().split()
        tmp = inp[0]
        fac.append(int(inp[1]))
        cost.append(int(inp[2]))
        xx = tmp[1]
        if xx == 'r':
            typ.append(1)
	elif xx == 'o':
            typ.append(2)
	else:
            typ.append(3)
    for i in xrange(n-1, -1, -1):
        for go in xrange(c, -1, -1):
            for s in xrange(10000, -1, -1):
                res = tab[go][s]
                r = g - cost[i]
                if typ[i] == 1:
                    if(s >= cost[i]):
                        res = max(res, 1 + tab[go][s-cost[i]])
                    tab[go][s] = res
                    if(go > 0):
                        r = r / fac[i] * fac[i]
                        res = max(res, 1 + tab[go-1][s+r])
                elif typ[i] == 2:
                    if(s >= cost[i]):
                        res = max(res, 1 + tab[go][s-cost[i]])
                    tab[go][s] = res
                    if(go > 0):
                        r = (r + fac[i]/2) / fac[i] * fac[i]
                        res = max(res, 1 + tab[go-1][s+r])
                else: 
                    if( s >= cost[i]):
                        res = max(res, 1 + tab[go][s-cost[i]])
                    elif(go > 0) :
                        r = (r + fac[i] - 1) / fac[i] * fac[i]
                        res = max(res, 1 + tab[go-1][s+r])
                tab[go][s] = res
    print(tab[c][0])

main()
