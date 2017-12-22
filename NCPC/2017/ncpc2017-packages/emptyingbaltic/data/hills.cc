//Solution by lukasP (Lukáš Poláček)
#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <random>
#include <set>
#include <tuple>
#include <unistd.h>
#include <vector>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef pair<int, int> pii;
int random_interval(default_random_engine& generator) {
    int low, high;
    cin >> low >> high;
    return (uniform_int_distribution<>(low, high))(generator);
}
const int MAX_DEPTH = 1000000;
int main() {
    random_device rd;
    default_random_engine generator(rd());

    string size_type; cin >> size_type;
    int h, w, num_tops;
    if (size_type == "random") {
        h = random_interval(generator);
        w = random_interval(generator);
        num_tops = random_interval(generator);
    } else if (size_type == "exactly") {
        cin >> h >> w >> num_tops;
    }
    cout << h << " " << w << endl;

    int depth[h][w];
    bool seen[h][w];
    rep(i,0,h) rep(j,0,w) seen[i][j] = false;

    vector<pii> tops;
    uniform_int_distribution<> x_distribution(0, h - 1);
    uniform_int_distribution<> y_distribution(0, w - 1);
    uniform_int_distribution<> depth_distribution(-MAX_DEPTH, -MAX_DEPTH * 8 / 10);

    set<pair<int, pii>> candidates;
    rep(i,0,num_tops) {
        tops.emplace_back(x_distribution(generator), y_distribution(generator));
        const pii& cur = tops.back();
        candidates.insert({depth_distribution(generator), cur});
    }

    int depth_step = MAX_DEPTH / max(h, w) * 4;
    uniform_int_distribution<> step_distr(depth_step * 2 / 5, depth_step);

    while (!candidates.empty()) {
        int x, y;
        tie(x, y) = candidates.begin()->second;
        int d = candidates.begin()->first;
        candidates.erase(candidates.begin());
        if (seen[x][y]) continue;
        depth[x][y] = d;
        seen[x][y] = true;

        rep(i,-1,2) rep(j,-1,2) {
            int nx = x + i;
            if (nx < 0 || nx >= h) continue;
            int ny = y + j;
            if (ny < 0 || ny >= w) continue;
            if (seen[nx][ny]) continue;
            int new_depth = depth[x][y] + step_distr(generator);
            candidates.insert({new_depth, make_pair(nx, ny)});
        }
    }

    rep(i,0,h) {
        rep(j,0,w) {
            printf("%d", depth[i][j]);
            printf(j + 1 < w ? " " : "\n");
        }
    }

    pii placement = tops[uniform_int_distribution<>(0, tops.size() - 1)(generator)];
    printf("%d %d\n", placement.first, placement.second);
}
