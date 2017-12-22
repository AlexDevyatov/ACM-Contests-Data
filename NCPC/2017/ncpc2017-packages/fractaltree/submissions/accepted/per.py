import sys
sys.setrecursionlimit(150000)

n = int(raw_input())

parents = [[0] + map(int, raw_input().split())]
children = [[] for _ in range(n)]
for (u, v) in zip(range(1, n), parents[0][1:]):
    children[v].append(u)

def dfs(u, d, order, depth):
    order.append(u)
    depth[u] = d
    for v in children[u]:
        dfs(v, d+1, order, depth)

order = []
depth = [0]*n
dfs(0, 0, order, depth)
rank = [0]*n
for i in range(n):
    rank[order[i]] = i

jmp = 1
while (1<<jmp) < n:
    parents.append([parents[jmp-1][parents[jmp-1][u]] for u in range(n)])
    jmp += 1

def Parent(u, d):
    b = 0
    while d:
        if d & (1<<b):
            u = parents[b][u]
            d -= (1<<b)
        b += 1
    return u

def Dist(u, v):
    if depth[u] < depth[v]: (u, v) = (v, u)
    du = depth[u]
    dv = depth[v]
    lo = du - dv - 1
    hi = n-1
    while hi - lo > 1:
        m = (lo + hi) / 2
        if Parent(u, m) == Parent(v, m - (du - dv)):
            hi = m
        else:
            lo = m
    return 2*hi - du + dv

k = int(raw_input()) + 1
leaves = sorted([i for i in range(n) if not children[i]],
                key = lambda x: rank[x])
sz = [1]
if len(leaves) > 1:
    while sz[-1] <= 2**30 and len(sz)-1 < k:
        sz.append(len(leaves) * (sz[-1] - 1) + n)
leading = rank[leaves[0]] * (k - len(sz) + 1)
k = len(sz)-1

def Label(a):
    if a < leading:
        return (a, [])
    a -= leading
    path = []
    k0 = k
    while True:
        lo = -1
        hi = len(leaves)-1
        while hi - lo > 1:
            m = (lo + hi)/2
            if a < rank[leaves[m]] + sz[k0-1] + m*(sz[k0-1] - 1):
                hi = m
            else:
                lo = m
        a -= hi*(sz[k0-1] - 1)
        u = leaves[hi]
        if a <= rank[u]:
            path.append(order[a])
            return (leading, path)
        path.append(u)
        a -= rank[u]
        k0 -= 1

def Solve(a, b):
    (LA, PA) = Label(a-1)
    (LB, PB) = Label(b-1)

    if LA < leading or LB < leading:
        return abs(LA + sum(depth[u] for u in PA) - LB - sum(depth[u] for u in PB))

    while len(PA) < len(PB): PA.append(0)
    while len(PB) < len(PA): PB.append(0)
    for i in range(len(PA)):
        if PA[i] != PB[i]:
            return Dist(PA[i], PB[i]) + sum(depth[u] for u in PA[i+1:]) + sum(depth[u] for u in PB[i+1:])

q = int(raw_input())
for _ in range(q):
    (a, b) = map(int, raw_input().split())
    print Solve(a, b)
