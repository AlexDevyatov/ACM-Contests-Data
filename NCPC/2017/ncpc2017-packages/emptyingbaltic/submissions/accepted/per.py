import heapq

(h, w) = map(int, raw_input().split())
grid = [1]*(w+2) + sum(([1]+map(int, raw_input().split()) + [1] for _ in range(h)), []) + [1]*(w+2)
(r, c) = map(int, raw_input().split())
w += 2
Q = [(grid[r*w+c], r*w+c)]
ans = 0
while Q:
    (d, x) = heapq.heappop(Q)
    if grid[x] >= 0: continue
    grid[x] = 0
    ans += -d
    for nx in [x-w-1, x-w, x-w+1, x-1, x+1, x+w-1, x+w, x+w+1]:
        if grid[nx] < 0:
            heapq.heappush(Q, (max(grid[nx], d), nx))

print ans
