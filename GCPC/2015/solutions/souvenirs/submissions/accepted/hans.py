from __future__ import print_function
from __future__ import division
try:
    import __builtin__
    input = getattr(__builtin__, 'raw_input', input)  # Python 3 (PEP 3111)
except:
    pass

G, C, N = [int(x) for x in input().split(' ')]
souv = [input().split(' ') for _ in range(N)]
souv = [(str(h), int(p), int(s)) for h, p, s in souv]

# res, N, C = silver
dp = [[[-1 for _ in range(5000+1)] for _ in range(C+1)] for _ in range(N+1)]

dp[0][C][0] = 0

result = 0
def update(n, c ,s, val):
    global result
    s = min(5000, s)
    dp[n][c][s] = max(dp[n][c][s], val)
    result = max(result, val)

for n in range(N):
    attitude, pkg, price = souv[n]
    change = G - price
    for c in range(C+1):
        for s in range(5000+1):
            res = dp[n][c][s]
            if res == -1:
                continue

            # don't buy
            update(n+1, c, s, res)

            if s >= price:
                update(n+1, c, s-price, res+1)

            if c < 1:
                continue

            if attitude == 'greedy':
                real_change = (change // pkg) * pkg
                update(n+1, c-1, s + real_change, res+1)
            elif attitude == 'honest':
                low_change = (change // pkg) * pkg
                high_change = ((change + pkg - 1) // pkg) * pkg
                if change - low_change < high_change - change:
                    real_change = low_change
                else:
                    real_change = high_change
                update(n+1, c-1, s + real_change, res+1)
            elif attitude == 'generous':
                if s < price:
                    real_change = ((change + pkg - 1) // pkg) * pkg
                    update(n+1, c-1, s + real_change, res+1)
            else:
                assert False

print(result)
