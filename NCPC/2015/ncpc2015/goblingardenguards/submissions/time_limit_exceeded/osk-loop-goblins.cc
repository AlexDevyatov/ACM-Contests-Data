#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {

    int g;
    cin >> g;
    vector<tuple<int,int>> goblins;
    vector<tuple<int,int,int>> sprinklers;
    vector<bool> marked(g, false);
    for (int i = 0; i < g; ++i) {
        int x, y;
        cin >> x >> y;
        goblins.push_back(make_tuple(x, y));
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        sprinklers.push_back(make_tuple(x,y,r));
    }
    int ans = 0;
    for (const auto &g : goblins) {
        const auto &gx = get<0>(g);
        const auto &gy = get<1>(g);    
        for (const auto &s : sprinklers) {
            const auto &sx = get<0>(s);
            const auto &sy = get<1>(s);
            const auto &sr = get<2>(s);
            if (abs(sx-gx) > sr || abs(sy-gy) > sr) continue;
            if ((sx-gx)*(sx-gx) + (sy-gy)*(sy-gy) <= sr*sr) {
                ++ans; break;
            }
        } 
    }
    cout << g-ans << endl;
}
