/* BFS-style solution.
 * - Start by draining start node.
 * - For each node u visited, check if any neighbor v of u has higher water
 *   level u.  If so, drain v down the level of u, and push v to queue.
 *
 * TIme complexity is O(max_d * w * h).
 * With large depths can make it Omega(w^2 * h^2)
 */
#include <bits/stdc++.h>

using namespace std;

int main(void) {
    int w, h;
    scanf("%d%d", &h, &w);
    int grid[500][500], water[500][500];
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) {
            scanf("%d", grid[i]+j);
            water[i][j] = max(0, -grid[i][j]);
        }
    int r, c;
    scanf("%d%d", &r, &c);
    --r; --c;

    queue<int> Q;
    Q.push(r*w + c);
    long long ans = water[r][c];
    water[r][c] = 0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        int r = u / w, c = u % w;
        int cur = grid[r][c] + water[r][c];
        for (int nr = r-1; nr <= r+1; ++nr) {
            if (nr < 0 || nr >= h) continue;
            for (int nc = c-1; nc <= c+1; ++nc) {
                if (nc < 0 || nc >= w || (nr == r && nc == c)) continue;
                if (cur < grid[nr][nc] + water[nr][nc] && water[nr][nc]) {
                    int drain = water[nr][nc] - max(0, cur - grid[nr][nc]);
                    ans += drain;
                    water[nr][nc] -= drain;
                    Q.push(nr*w + nc);
                }
            }
        }
    }
    printf("%lld\n", ans);
}
