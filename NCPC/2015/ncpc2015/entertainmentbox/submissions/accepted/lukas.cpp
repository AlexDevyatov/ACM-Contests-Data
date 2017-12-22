//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef pair<int, int> pii;

struct Node {
    int s, e;
    int max;
    int add;
    int getMax() { return max + add; }
    Node() : max(0), add(0) {}
};

struct Tree {
    int n;
    vector<Node> s;
    Tree(int _n) {
        n = 1; while (n < _n) n *= 2;
        s.resize(2 * n);
        rep(i,n,2*n)
        {
            s[i].s = i - n;
            s[i].e = s[i].s + 1;
        }
        for (int i = n - 1; i >= 1; i--)
        {
            s[i].s = s[2 * i].s;
            s[i].e = s[2 * i + 1].e;
        }
    }

    int query(int a, int b) { return que(1, a, b); }
    void update(int a, int b) { upd(1, a, b); }
    private:
    int que(int pos, int a, int b) {
        if (a >= b) return 0;
        if (a == s[pos].s && b == s[pos].e) return s[pos].getMax();
        int m = (s[pos].s + s[pos].e) / 2;
        return max(que(2 * pos, a, min(b, m)), que(2 * pos + 1, max(a, m), b)) + s[pos].add;
    }

    void upd(int pos, int a, int b) {
        if (a >= b) return;
        if (a == s[pos].s && b == s[pos].e)
        {
            s[pos].add++;
            return;
        }
        int m = (s[pos].s + s[pos].e) / 2;
        upd(2 * pos, a, min(b, m));
        upd(2 * pos + 1, max(a, m), b);
        s[pos].max = max(s[2 * pos].getMax(), s[2 * pos + 1].getMax());
    }
};
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

    Tree t(u);
    sort(intervals.begin(), intervals.end());
    int res = 0;
    for (pii &o : intervals)
    {
        pii z(ord[o.second], ord[o.first]);
        int q = t.query(z.first, z.second);
        if (q < k)
        {
            t.update(z.first, z.second);
            res++;
        }
    }

    cout << res << endl;
}
