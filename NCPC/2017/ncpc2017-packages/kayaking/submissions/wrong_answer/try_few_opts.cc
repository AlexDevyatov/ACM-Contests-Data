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
    vector<int> goals;
    for (int i = 0; i < m; ++i) {
        scanf("%d", &c[i]);
        for (int t1 = 0; t1 < 3; ++t1)
            for (int t2 = t1; t2 < 3; ++t2)
                goals.push_back(c[i]*(s[t1]+s[t2]));
    }
    sort(c.begin(), c.end());

    sort(goals.begin(), goals.end());
    goals.resize(unique(goals.begin(), goals.end()) - goals.begin());
    // Ooops only keeps 10000 worst possible OPTs and does linear scan among those
    if (goals.size() > 10000) goals.resize(10000);
    reverse(goals.begin(), goals.end());
    for (auto goal: goals) {
        if (check(n, s, types, c, goal)) {
            printf("%d\n", goal);
            break;
        }
    }
    return 0;
}
