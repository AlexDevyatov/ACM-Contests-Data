#!/usr/bin/env python
# -*- coding: utf-8
#Solution by lukasP (Luká¿ Polá¿ek)
from sys import stdin

pr = [0.0] * 210
win, tie = 0.0, 0.0

for i in range(2):
    x = list(map(int, stdin.readline().split()))

    sz = float(x[1] - x[0] + 1) * (x[3] - x[2] + 1)
    for j in range(x[0], x[1] + 1):
        for l in range(x[2], x[3] + 1):
            if i == 1:
                win += pr[j + l - 1] / sz
                tie += (pr[j + l] - pr[j + l - 1]) / sz
            else:
                pr[j + l] += 1 / sz

    if i == 0:
        for j in range(1, len(pr)):
            pr[j] += pr[j - 1]

suma = win * 2 + tie;
if abs(suma - 1) < 1e-9:
    print("Tie")
else:
    print("Emma" if suma > 1 else "Gunnar")
