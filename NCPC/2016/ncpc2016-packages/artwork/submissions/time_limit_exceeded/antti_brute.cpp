#include <iostream>

using namespace std;

int n, m, q;
int t[1111][1111];

void dfs(int y, int x) {
    if (y < 1 || x < 1 || y > n || x > m) return;
    if (t[y][x] != 0) return;
    t[y][x] = 2;
    dfs(y-1,x);
    dfs(y+1,x);
    dfs(y,x-1);
    dfs(y,x+1);
}

int calc() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (t[i][j] != 1) t[i][j] = 0;
        }
    }
    int c = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (t[i][j] == 0) {
                dfs(i,j);
                c++;
            }
        }
    }
    return c;
}

int main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                t[i][j] = 1;
            }
        }
        cout << calc() << "\n";
    }
}
