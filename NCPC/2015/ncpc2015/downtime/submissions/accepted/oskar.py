import sys

if __name__ == "__main__":
    N, K = map(int, sys.stdin.readline().strip().split())
    l = [0] * 101001
    for i in xrange(N):
        ti = int(sys.stdin.readline().strip())
        l[ti] += 1
        l[ti + 1000] -= 1
    top = 0
    accum = 0
    for i in xrange(101001):
        accum += l[i]
        top = max(top, accum)
    print ((top + K - 1) // K)
