n = int(raw_input())

speeds = sorted([(float(b), float(c), a) for (a, b, c) in [raw_input().split() for _ in range(n)]])
runners = speeds[:4]

speeds = sorted(speeds, key = lambda x: x[1])
runners.extend(speeds[:4])

best = (1e30,)
for r1 in runners:
    for r2 in runners:
        for r3 in runners:
            for r4 in runners:
                if r1 != r2 and r1 != r3 and r1 != r4 and r2 != r3 and r2 != r4 and r3 != r4:
                    time = r1[0] + r2[1] + r3[1] + r4[1]
                    if time < best[0]:
                        best = (time, r1, r2, r3, r4)

print('%.2f' % best[0])
for i in range(1, 5):
    print('%s' % best[i][2])
