(n, k) = map(int, raw_input().split())
K = 1<<k
dist = [K]*(K)

Q = [int(raw_input(), 2) for _ in range(n)]
qh = 0
for x in Q:
    dist[x] = 0

while qh < len(Q):
    x = Q[qh]
    qh += 1
    for i in range(k):
        y = x ^ (1<<i)
        if dist[y] > dist[x] + 1:
            Q.append(y)
            dist[y] = dist[x] + 1

ans = bin(x)[2:]
ans = '0'*(k-len(ans)) + ans
print ans
