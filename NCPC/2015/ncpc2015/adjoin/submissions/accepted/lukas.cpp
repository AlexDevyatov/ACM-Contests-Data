//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
int f(int x)
{
    return (x + 1) / 2;
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    vector<vi> g(n);
    vi cnt(n), dist(n);
    rep(i,0,m)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
        cnt[a]++;
        cnt[b]++;
    }

    queue<int> q;
    rep(i,0,n) if (cnt[i] == 1)
        q.push(i);

    for (; !q.empty(); q.pop())
    {
        int u = q.front();
        for (int x : g[u]) if (--cnt[x] == 1)
        {
            q.push(x);
            dist[x] = dist[u] + 1;
        }
    }

    vi type(n, -1);
    rep(i,0,n)
    {
        auto same_dist = [&dist, &i](int const x) { return dist[x] == dist[i]; };
        auto as_outer = [&dist, &i](int const x) { return dist[x] <= dist[i]; };
        if (all_of(g[i].begin(), g[i].end(), as_outer))
        {
            type[i] = any_of(g[i].begin(), g[i].end(), same_dist);
            auto earlier = [&dist, &i](int const x) { return dist[x] == dist[i] && x < i; };
            if (type[i] && none_of(g[i].begin(), g[i].end(), earlier))
                type[i] = -1; // only mark one center
        }
    }

    vi components;
    rep(i,0,n) if (type[i] >= 0)
        components.push_back(dist[i] * 2 + type[i]);

    sort(components.begin(), components.end(), greater<int> ());
    int res = components[0];
    if (components.size() > 1)
        res = max(res, 1 + f(components[0]) + f(components[1]));
    if (components.size() > 2)
        res = max(res, 2 + f(components[1]) + f(components[2]));
    cout << res << endl;
}
