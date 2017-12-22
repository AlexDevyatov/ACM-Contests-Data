#!/usr/bin/env python3

(n, m) = map(int, input().split())

score = [(0, 0)] * (n+1)
better = set()

for _ in range(m):
    (t, p) = [int(x) for x in  input().split()]
    score[t] = (score[t][0] + 1, score[t][1] - p)
    if score[t] > score[1]:
        better.add(t)
    if t == 1:
        better = set([i for i in better if score[i] > score[1]])
    print(len(better)+1)
