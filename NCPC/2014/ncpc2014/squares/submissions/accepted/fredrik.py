# Solution of problem Clock Pictures
# Time complexity: O(n*n*log(n))
# Author: Fredrik Svensson
import sys
import fractions

# Rotates the normal to 1 and 2 quadrant, 0 <= angle < 180
def rotateNormal(n):
    if n[1] < 0 or (n[1] == 0 and n[0] < 0):
        n = (-n[0], -n[1])
    return n

n = int(sys.stdin.readline())
# Storing (nx, ny, dist) such as nx*x+ny*y-dist=0
# Normals in quadrant 1+2, as short as possible (divided by gcd)
# Distances can be thought as scaled by (nx*nx+ny*ny).
lines = {}  # normal: [distance]
for i in range(n):
    (x1, y1, x2, y2) = map(int, sys.stdin.readline().split())
    dx = x2-x1
    dy = y2-y1
    d = fractions.gcd(abs(dx), abs(dy))
    dx /= d
    dy /= d
    n = rotateNormal((-dy, dx))
    dist = x1*n[0] + y1*n[1]
    assert dist == x2*n[0] + y2*n[1]
    lines.setdefault(n, []).append(dist)

# Calculate all pairwise distances
linesdiffs = {}  # normal: {distance_difference: count}
for n, dists in lines.items():
    distdiffs = {}
    for i in range(len(dists)):
        for j in range(i+1, len(dists)):
            distdiff = abs(dists[i]-dists[j])
            distdiffs[distdiff] = distdiffs.get(distdiff, 0)+1
    linesdiffs[n] = distdiffs

# Count...
ret = 0
for n, ndistdiffs in linesdiffs.items():
    p = rotateNormal((n[1], -n[0]))  # Perpendicular to the normal
    pdistdiffs = linesdiffs.get(p, {})
    for ndistdiff, ncount in ndistdiffs.items():
        pcount = pdistdiffs.get(ndistdiff, 0)
        ret += ncount * pcount

# Print result
assert ret % 2 == 0
print(ret / 2)
