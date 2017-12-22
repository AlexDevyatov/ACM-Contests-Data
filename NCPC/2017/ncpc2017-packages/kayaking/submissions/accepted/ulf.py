#!/usr/bin/env python3
def possible(v):
    a = [sum([ci*ssi >= v for ci in c]) for ssi in ss]
    if a[5] < len(c):
        return False
    da = [a[0]] + [a[i]-a[i-1] for i in range(1,len(a))]
    da[4] += min(0, da[3])
    nn = list(n)
    nn[0] -= da[0]*2 + da[1]
    nn[1] -= da[1] + da[4]
    nn[2] -= da[5]*2 + da[4]
    if da[3] > 0:
        nn[1] -= da[3]*2
        r = da[2]
    else:
        nn[0] -= -da[3]
        nn[2] -= -da[3]
        r = da[2] + da[3]
    b = max(0, min(nn[0], r))
    nn[0] -= b
    nn[2] -= b
    nn[1] -= 2 * (r-b)
    return nn[2] >= 0 and nn[2]+nn[1] >= 0

n = [int(a) for a in input().split()]
s = [int(a) for a in input().split()]
c = sorted([int(a) for a in input().split()])
ss = [s[0]*2, s[0]+s[1], s[0]+s[2], s[1]*2, s[1]+s[2], s[2]*2]
speeds = sorted([ci*ssi for ci in c for ssi in ss])
lb, ub = 0, len(speeds)
while ub-lb > 1:
    m = (ub+lb)//2
    if possible(speeds[m]):
        lb = m
    else:
        ub = m
print(speeds[lb])
