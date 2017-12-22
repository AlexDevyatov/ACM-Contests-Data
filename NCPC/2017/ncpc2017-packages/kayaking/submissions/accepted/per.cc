#include <bits/stdc++.h>
using namespace std;

bool check(vector<int> n, vector<int> s,
           vector<pair<int, int>> types,
           vector<int> c, int goal) {
    for (auto &T: types) {
        int S = s[T.first] + s[T.second];
        while (!c.empty() && n[T.first] >= 1 + (T.first == T.second) && n[T.second] >= 1 && c.back()*S >= goal) {
            c.pop_back();
            --n[T.first];
            --n[T.second];
        }
    }
    return c.empty();
}

int main(void) {
    vector<int> n(3), s(3);
    scanf("%d%d%d%d%d%d", &n[0], &n[1], &n[2], &s[0], &s[1], &s[2]);
    vector<pair<int, int>> types;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j <= i; ++j)
            types.push_back(make_pair(i, j));
    sort(types.begin(), types.end(), [&s](pair<int, int> a, pair<int, int> b) {
            return s[a.first]+s[a.second] < s[b.first]+s[b.second]; });

    int m = (n[0]+n[1]+n[2])/2;
    vector<int> c(m);
    for (int i = 0; i < m; ++i)
        scanf("%d", &c[i]);
    sort(c.begin(), c.end());

    int lo = 0, hi = 1<<30;
    while (hi - lo > 1) {
        int goal = (lo+hi)/2;
        (check(n, s, types, c, goal) ? lo : hi) = goal;
    }
    printf("%d\n", lo);
    return 0;
}
