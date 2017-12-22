#!/usr/bin/env python3
from sys import stdin

C,n = map(int, stdin.readline().split())
current = 0
consistent = False

for t in range(n):
    a,b,c = map(int, stdin.readline().split())
    current -=a
    current +=b
    if current < 0 : break
    if current > C : break
    if c and current < C : break
else:
    consistent = (current==0)

print("possible" if consistent else "impossible")
