n = int(raw_input())
speeds = sorted([(float(b), float(c), a) for (a, b, c) in [raw_input().split() for _ in range(n)]])

best = (1e30,)
for a in range(n):
    for b in range(a):
        for c in range(b):
            for i in range(n):
                if i != a and i != b and i != c:
                    time = speeds[i][0] + speeds[a][1] + speeds[b][1] + speeds[c][1]
                    if time < best[0]:
                        best = (time, i, a, b, c)
                    break

print('%.2f' % best[0])
for i in range(1, 5):
    print('%s' % speeds[best[i]][2])
