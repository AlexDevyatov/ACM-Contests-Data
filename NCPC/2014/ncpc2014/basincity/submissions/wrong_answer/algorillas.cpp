#include <string>
#include <cstdio>

using namespace std;

int nb[100001][4];
int taken[100001];
int n;
int cnt;

inline int optimal() {
    int b=5;
    int k=0;
    for (int i=1;i<=n;i++) {
        if (taken[i] == 0) {
            int t = 0;
            t += !taken[nb[i][0]] + !taken[nb[i][1]] + !taken[nb[i][2]] + !taken[nb[i][3]];
            if (t < b) {
                if (t == 1) return i;
                b = t;
                k = i;
            }
        }
    }
    return k;
}

bool rec(int curr, int k) {
    ++cnt;
    if (cnt > 10000000) return false;
    if (curr == 0) return false;
     // printf("rec(%d,%d)\n", curr, k);
    if (k == 1) return true;
    // Try with this node first
    ++taken[curr];
    for (int i = 0; i < 4; ++i) ++taken[nb[curr][i]];
    bool ok = rec(optimal(), k-1);
    // if (ok) printf("rec(%d,%d)\n", curr, k);
    if (ok) return true;
    --taken[curr];
    for (int i = 0; i < 4; ++i) --taken[nb[curr][i]];

    // If not this one, we can safely assume we MUST use one of his neighbors
    for (int i = 0; i < 4; ++i) {
        if (!taken[nb[curr][i]]) {
            int next = nb[curr][i];
            ok = false;
            ++taken[next];
            for (int j = 0; j < 4; ++j) ++taken[nb[next][j]];

            ok = rec(optimal(), k-1);
            if (ok) return true;

            --taken[next];
            for (int j = 0; j < 4; ++j) --taken[nb[next][j]];
        }
    }
    return false;
}

int main() {
    int k, m, tmp;
    scanf("%d", &k);
    scanf("%d", &n);
    taken[0] = 1;
    for (int i = 1; i <= n; ++i) {
        taken[i] = 0;
        scanf("%d", &m);
        for (int j = 0; j < 4; ++j) nb[i][j] = 0;
        for (int j = 0; j < m; ++j) {
            scanf("%d", &tmp);
            nb[i][j] = tmp;
        }
    }

    cnt = 0;
    bool ok = rec(optimal(),k);
    if (ok) printf("possible\n");
    else printf("impossible\n");
    return 0;
}
