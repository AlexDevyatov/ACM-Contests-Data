//Solution by lukasP (Lukáš Poláček)
#include <cstdio>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
typedef pair<int, int> pii;
const int MAX = 1000;
int depths[MAX][MAX];
int best[MAX][MAX];
int main() {
    int h, w;
    scanf("%d %d", &h, &w);

    rep(i,0,h) rep(j,0,w) {
        scanf("%d", &depths[i][j]);
        best[i][j] = 123456789;
    }

    int sx, sy;
    scanf("%d %d", &sx, &sy);
    sx--; sy--;
    set<pair<int, pii>> candidates;
    best[sx][sy] = depths[sx][sy];
    candidates.insert({depths[sx][sy], {sx, sy}});

    ll water_removed = 0;
    while (!candidates.empty()) {
        int depth = candidates.begin()->first;
        int x, y;
        std::tie(x, y) = candidates.begin()->second;
        candidates.erase(candidates.begin());
        water_removed += max(0, -depth);
        rep(i,-1,2) rep(j,-1,2) {
            int nx = x + i;
            int ny = y + j;
            if (nx < 0 || nx >= h) continue;
            if (ny < 0 || ny >= w) continue;
            int new_depth = max(depth, depths[nx][ny]);
            if (new_depth < best[nx][ny]) {
                const auto iter = candidates.find({best[nx][ny], {nx, ny}});
                if (iter != candidates.end()) candidates.erase(iter);
                best[nx][ny] = new_depth;
                candidates.insert({best[nx][ny], {nx, ny}});
            }
        }
    }

    cout << water_removed << endl;
}
