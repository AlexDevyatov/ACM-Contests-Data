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
        return [0, 1]
    return [0] if dA < dB else [1]


(n, m) = map(int, raw_input().split())
citizens = sorted([map(int, raw_input().split()) + [i] for i in range(n)], cmp = angle_cmp)
trains = sorted([map(int, raw_input().split()) + [i] for i in range(m)], cmp = angle_cmp)

t = 0
cands = [None]*n
for i in range(n):
    while t < m and angle_cmp(trains[t], citizens[i]) < 0:
        t += 1
    neighs = find_closest(citizens[i], trains[t%m], trains[t-1])
    cands[i] = [(t-j) % m for j in neighs]

val = [0, 0]
assign = [[None]*n for _ in range(2)]
idx = range(n)
for s in [0, 1]:
    cap = [t[2] for t in trains]
    for i in idx:
        cands[i].reverse()
        for j in cands[i]:
            if cap[j]:
                assign[s][i] = j
                val[s] += 1
                cap[j] -= 1
                break
    idx.reverse()

print max(val[0], val[1])
sol = assign[0] if val[0] >= val[1] else assign[1]
for i in range(n):
    if sol[i] is not None:
        print '%d %d' % (citizens[i][2], trains[sol[i]][3])
