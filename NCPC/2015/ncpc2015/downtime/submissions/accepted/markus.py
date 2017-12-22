from sys import stdin

n, k = map(int, stdin.readline().split())
timestamps = [int(stdin.readline()) for i in range(n)]

active, max_active, i, j = 0, 0, 0, 0
for t in range(2**17):
    while i < n and timestamps[i]+1000 == t:
        active -= 1
        i += 1

    while j < n and timestamps[j] == t:
        active += 1
        j += 1

    max_active = max(max_active, active)

print max_active/k + (1 if max_active%k != 0 else 0)
