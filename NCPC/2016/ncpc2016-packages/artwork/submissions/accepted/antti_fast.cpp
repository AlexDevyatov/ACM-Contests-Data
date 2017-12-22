#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n, m, q;
set<int> xs[1111], ys[1111];
vector<pair<int,int>> v[1111111];

int c[1111][1111];
int w[1111111];
int s[1111111];
int z;
int u;

void merge(int y1, int x1, int y2, int x2) {
    if (c[y1][x1] == 0 || c[y2][x2] == 0) return;
    int c1 = c[y1][x1];
    int c2 = c[y2][x2];
    while (c1 != w[c1]) c1 = w[c1];
    while (c2 != w[c2]) c2 = w[c2];
    if (c1 == c2) return;
    u--;
    if (s[c1] > s[c2]) {
        s[c1] += s[c2];
        w[c2] = c1;
    } else {
        s[c2] += s[c1];
        w[c1] = c2;
    }
}

void change(int y, int x) {
    c[y][x] = ++z;
    w[z] = z;
    s[z] = 1;
    u++;
    merge(y,x,y-1,x);
    merge(y,x,y+1,x);
    merge(y,x,y,x-1);
    merge(y,x,y,x+1);
}

int main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ys[i].insert(j);
            xs[j].insert(i);
        }
    }
    for (int i = 1; i <= q; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        if (y1 == y2) {
            auto it = ys[y1].lower_bound(x1);
            while (it != ys[y1].end() && *it <= x2) {
                v[i].push_back({y1,*it});
                auto it2 = it;
                it2++;
                xs[*it].erase(y1);
                ys[y1].erase(*it);
                it = it2;
            }
        } else {
            auto it = xs[x1].lower_bound(y1);
            while (it != xs[x1].end() && *it <= y2) {
                v[i].push_back({*it,x1});
                auto it2 = it;
                it2++;
                ys[*it].erase(x1);
                xs[x1].erase(*it);
                it = it2;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (auto x : ys[i]) {
            v[q+1].push_back({i,x});
        }
    }
    vector<int> r;
    for (int i = q+1; i >= 1; i--) {
        for (auto j : v[i]) {
            change(j.first,j.second);
        }
        r.push_back(u);
    }
    for (int i = q-1; i >= 0; i--) {
        cout << r[i] << "\n";
    }
}
