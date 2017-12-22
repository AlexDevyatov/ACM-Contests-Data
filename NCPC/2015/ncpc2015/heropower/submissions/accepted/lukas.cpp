//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
void improveMax(int &a, int b)
{
    a = max(a, b);
}
int main()
{
    int n, p;
    scanf("%d %d", &n, &p);

    unordered_map<int, int> ord;
    vi t(n);
    rep(i,0,n) {
        scanf("%d", &t[i]);
        ord[t[i]] = i;
    }

    vi next, starts(p), totpow;
    rep(i,0,p)
    {
        int s, e; scanf("%d %d", &s, &e);
        starts[i] = ord[s];
        next.resize(starts[i], i);
        totpow.resize(starts[i] + 1, (totpow.empty() ? 0 : totpow.back()));
        rep(j,ord[s],ord[e])
            totpow.push_back(totpow.back() + t[j + 1] - t[j]);
    }
    totpow.resize(n, totpow.back());
    next.resize(n, p);

    vi best(p + 1);
    rep(i,0,p)
    {
        int point = starts[i];
        rep(j,point+1,n)
        {
            while (point + 1 < n && totpow[point + 1] - totpow[starts[i]] <= t[j] - t[point + 1])
                point++;
            improveMax(best[next[j]], best[i] + (j - point));
        }
    }
    cout << best[p] + n << endl;
}
