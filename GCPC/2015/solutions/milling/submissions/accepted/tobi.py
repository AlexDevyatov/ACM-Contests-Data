import sys
def main():
    W, S = [int(x) for x in sys.stdin.readline().split()]
    X, Y = [int(x) for x in sys.stdin.readline().split()]

    Ws = []
    for lind in range(W):
        Ws.append([int(k) for k in sys.stdin.readline().split()])

    M = [0 for k in range(X)]
    for i in range(S):
        step = [int(k) for k in sys.stdin.readline().split()]
        for j in range(X):
            M[j] = max(M[j], step[j])

    for i in range(W):
        for j in range(X):
            Ws[i][j] = min(Ws[i][j], Y-M[j]);
            if (j != 0):
                sys.stdout.write(" ");
            sys.stdout.write(str(Ws[i][j]));
        sys.stdout.write("\n");

main()
