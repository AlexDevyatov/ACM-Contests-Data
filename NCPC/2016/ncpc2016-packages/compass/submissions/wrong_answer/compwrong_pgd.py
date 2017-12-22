#!/usr/bin/env python3
import sys

a,b = map(int, sys.stdin.read().split())
d = abs(a-b)
if d > 180:
    d -= 180
if (a + d) % 360 == b:
    print(d)
elif (a - d) % 360 == b:
    print(-d)
elif (b + d) % 360 == a:
    print(-d)
elif (b - d) % 360 == a:
    print(d)
else:
    print(d)
