from sys import stdin
import re, sys

n = int(stdin.readline())
r1 = []
r2 = []
for i in range(0,n):
    name, t1, t2 = stdin.readline().strip().split(' ')
    r1.append((name, float(t1), float(t2)))
    r2.append((name, float(t1), float(t2)))

r1.sort(key=lambda x: x[1])
r2.sort(key=lambda x: x[2])

best_time = 999.99
for i in range(0,4):
    for j in range(0,4):
        for k in range(j+1,4):
            for l in range(k+1,4):
                tm = r1[i][1] + r2[j][2] + r2[k][2] + r2[l][2]
                if tm < best_time and r1[i][0] not in [r2[j][0], r2[k][0], r2[l][0]]:
                    best_time = tm
                    best = (r1[i][0], r2[j][0], r2[k][0], r2[l][0])

print best_time
for i in range(0,4):
    print best[i]
