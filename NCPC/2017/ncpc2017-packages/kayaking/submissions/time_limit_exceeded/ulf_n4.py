#!/usr/bin/env python3
n = [int(a) for a in input().split()]
s = [int(a) for a in input().split()]
c = sorted([int(a) for a in input().split()])

fastest = 0

for n01 in range(min(n[0:1])+1):
    for n02 in range(min(n[0]-n01, n[2])+1):
        n00 = n[0] - n01 - n02
        if n00%2:
            continue
        n00 //= 2
        for n12 in range(min(n[1]-n01, n[2]-n02)+1):
            n11 = n[1] - n01 - n12
            n22 = n[2] - n02 - n12
            if n11%2 or n22%2:
                continue
            n11 //= 2
            n22 //= 2
            P = sorted([s[0]+s[1]]*n01 + [s[0]+s[2]]*n02 + [s[1]+s[2]]*n12 + [2*s[0]]*n00 + [2*s[1]]*n11 + [2*s[2]]*n22)
            slowest = float("inf")
            for i in range(len(c)):
                slowest = min(slowest, c[i]*P[len(c)-i-1])
            fastest = max(fastest, slowest)
print(fastest)
