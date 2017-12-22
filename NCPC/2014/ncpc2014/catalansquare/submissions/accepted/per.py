import sys

n = int(sys.stdin.readline())
C = [0]*(n+2)
C[0] = 1
for i in range(1, n+2):
    # (n+1)*C_n = (2n)!/(n!*n!) = (2n-2)!*(2n-1)*2n / ((n-1)!^2*n^2)
    # = C_n-1*(2n-1)*2
    # C_n = C_{n-1}*2*(2n-1)/(n+1)
    C[i] = C[i-1]*2*(2*i-1)/(i+1)

print C[n+1]
