# Abusing duck typing for fun and profit
import math

def sgn(x): return 1 if x > 0 else -1 if x < 0 else 0

def cross(P, Q):
    return P[0]*Q[1] - Q[0]*P[1]

def angle_cmp(P, Q):
    hp = P[1] > 0 or P[1] == 0 and P[0] < 0
    hq = Q[1] > 0 or Q[1] == 0 and Q[0] < 0
    if hp != hq:
        return hq - hp
    return cross(Q, P)

def find_closest(P, A, B):
    vP = math.atan2(P[1], P[0])
    dA = math.atan2(A[1], A[0]) - vP
    dB = vP - math.atan2(B[1], B[0])
    if dA < 0: dA += 2*math.pi
    if dB < 0: dB += 2*math.pi
    if abs(dA-dB) < 1e-13:
        return [1, 0]
    return [0] if dA < dB else [1]


(n, m) = map(int, raw_input().split())
citizens = sorted([map(int, raw_input().split()) + [i] for i in range(n)], cmp = angle_cmp)
trains = sorted([map(int, raw_input().split()) + [i] for i in range(m)], cmp = angle_cmp)

t = 0
cands = []
groups = []
for i in range(n):
    if i and not angle_cmp(citizens[i-1], citizens[i]):
        groups[-1][0].append(i)
    else:
        while t < m and angle_cmp(trains[t], citizens[i]) < 0:
            t += 1
        neighs = find_closest(citizens[i], trains[t%m], trains[t-1])
        groups.append([[i], [(t-j) % m for j in neighs]])

sol = []
n = len(groups)
remaining = []
for (ppl, trn) in groups:
    if len(trn) == 1:
        j = trn[0]
        while ppl and trains[j][2]:
            sol.append((ppl[-1], j))
            ppl.pop()
            trains[j][2] -= 1
    else:
        remaining.append((ppl, trn))


groups = remaining
n = len(groups)

backw = [0]*n
forw = [0]*n
cap = [t[2] for t in trains]
for (i, (ppl, [b, f])) in enumerate(groups):
    backw[i] = min(len(ppl), cap[b])
    forw[i] = min(len(ppl)-backw[i], cap[f])
    cap[b] -= backw[i]
    cap[f] -= forw[i]
    surplus = len(ppl) - forw[i] - backw[i]

filled = 0
for (i, (ppl, [b, f])) in enumerate(groups):
    surplus = min(surplus, backw[i], trains[f][2] - forw[i])
    fill = min(cap[f], surplus)
    filled += fill
    surplus -= fill

if n: forw[-1] += filled
surplus = filled
for (i, (ppl, [b, f])) in enumerate(groups):
    backw[i] -= surplus
    forw[i] += surplus
    fill = min(cap[f], surplus)
    surplus -= fill
    for j in range(backw[i]):
        sol.append((ppl[-1], b))
        ppl.pop()
    for j in range(forw[i]):
        sol.append((ppl[-1], f))
        ppl.pop()

print len(sol)
for (i, j) in sol:
    print '%d %d' % (citizens[i][2], trains[j][3])
