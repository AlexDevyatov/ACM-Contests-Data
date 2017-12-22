//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    set<int> w;
    vector<pii> intervals(n);
    rep(i,0,n)
    {
        scanf("%d %d", &intervals[i].second, &intervals[i].first);
        w.insert(intervals[i].first);
        w.insert(intervals[i].second);
    }

    unordered_map<int, int> ord;
    int u = 0;
    for (int x : w)
        ord[x] = u++;

    vector<int> s(u);
    sort(intervals.begin(), intervals.end());
    int res = 0;
    for (pii &o : intervals)
    {
        pii z(ord[o.second], ord[o.first]);
        bool ok = true;
        rep(i,z.first,z.second)
            if (s[i] >= k) { ok = false; break; }
        if (ok)
        {
            for (int i = z.first; i < z.second; i++)
                s[i]++;
            res++;
        }
    }

    cout << res << endl;
}
