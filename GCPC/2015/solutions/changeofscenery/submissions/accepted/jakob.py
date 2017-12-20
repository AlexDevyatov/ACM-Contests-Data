import sys, heapq

myin = [int(x) for x in sys.stdin.read().split()]
cons = 0
n, m, k = myin[cons:cons+3]
cons += 3

shortest = myin[cons:cons+k]
cons += k

graph = [{} for b in range(n+1)]
mult =  [{} for b in range(n+1)]

def readinput(cons):
    for i in range(m):
        ai = myin[cons]
        bi = myin[cons+1]
        ci = myin[cons+2]
        cons+=3
        if ai in graph[bi]:
            curr = graph[ai][bi]
            if ci < curr:
                graph[ai][bi] = graph[bi][ai] = ci
                mult[ai][bi] = mult[bi][ai] = False
            elif ci == curr:
                mult[ai][bi] = mult[bi][ai] = True
        else:
            graph[ai][bi] = graph[bi][ai] = ci

readinput(cons)

for fromind in range(len(shortest)-1):
    f = shortest[fromind]
    t = shortest[fromind+1]
    if t in mult[f] and mult[f][t]:
        print("yes")
        sys.exit(0)


def dijkstra():
    queue = [(0, 1)]
    vis = [False for x in range(n+1)]
    td = [2**32 for x in range(n+1)]
    while queue:
        dist, node = heapq.heappop(queue)
        #print(node, dist)
        if vis[node]:
            continue
        vis[node] = True
        td[node] = dist
        for neigh, strlen in graph[node].items():
            if vis[neigh]:
                continue
            newd = dist+strlen
            #print(">>", neigh, strlen, newd)
            if td[neigh] > newd:
                td[neigh] = newd
                heapq.heappush(queue, (newd, neigh))
    return td

dists = dijkstra()

for node in reversed(shortest[1:]):
    # print(node)
    npp = 0
    for pred, distprednode in graph[node].items():
        if dists[node] == dists[pred] + distprednode:
            # print(">>", pred)
            npp += 1
    if npp > 1:
        print("yes")
        sys.exit(0)

print("no")
sys.exit(0)
