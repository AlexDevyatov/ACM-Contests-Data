def printpath(u, v):
    for i in range(n):
        if dst[u][i] == 1 and (dst[i][v] == dst[u][v] - 1 or dst[u][v] == 1):
            print names[u]
            if dst[u][v] > 1:
                printpath(i, v);
            break

n = int(raw_input())
names = raw_input().split()
idx = dict(zip(names, range(n)))
dst = [[n+1]*n for _ in range(n)]

for i in range(n):
    (_, k) = raw_input().split()
    for _ in range(int(k)):
        for imp in raw_input().split()[1:]:
            if imp[-1] == ',': imp = imp[:-1]
            dst[i][idx[imp]] = 1

V = range(n)
for k in V:
    dk = dst[k]
    for i in V:
        di = dst[i]
        for j in V:
            di[j] = min(di[j], di[k] + dk[j]);

s = 0
for i in range(n):
    if dst[i][i] < dst[s][s]:
        s = i
if dst[s][s] <= n:
    printpath(s, s)
else:
    print "SHIP IT"
