// Author: Johan Sannemo
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef tuple<double, double, int> cart;

void insertInto(cart n, deque<cart> &q, double var) {
    auto cmp = [var](cart x) {
        return get<1>(x) + get<0>(x) / var;
    };
    while (!q.empty() && cmp(n) < cmp(q.front())) {
        q.pop_front();
    }
    q.push_front(n);
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    double l, a, b, t, r;
    cin >> l >> a >> b >> t >> r;

    int n;
    cin >> n;

    vector<double> P(n);
    trav(it, P) cin >> it;

    P.push_back(l+1e-10);
    l += 2e-10;
    reverse(all(P));
    P.push_back(-(t * a + r * b + 1e-10));

    vi optNext(sz(P));
    optNext[0] = -1;
    vector<double> opt(sz(P));
    deque<tuple<double, double, int>> waiting, drinking, done;
    int whas = 0, drhas = 0, dohas = 0;
    rep(i,1,sz(P)) {
        double pos = P[i];
        // Pop away everything in the queues that are too far away

        double waitingEndPos = pos + t * a;
        double drinkingEndPos = pos + t * a + r * b;
#define DOINTERVAL(idx, queue, var, left, right) \
        while (idx != i && P[idx] >= left) { \
            insertInto(make_tuple(P[idx], opt[idx], idx), queue, var); \
            ++idx; \
        } \
        while (!queue.empty() && get<0>(queue.back()) > right) { \
            queue.pop_back(); \
        }
        DOINTERVAL(whas, waiting, a, pos, waitingEndPos);
        DOINTERVAL(drhas, drinking, b, waitingEndPos, drinkingEndPos);
        DOINTERVAL(dohas, done, a, drinkingEndPos, l);


        double ans = 1e100;
        int ansi = -2;
#define SMIN(idx) if (nans < ans) { ans = nans; ansi = idx; }
        if (!waiting.empty()) {
            double nans = (get<0>(waiting.back()) - pos) / a + get<1>(waiting.back());
            SMIN(get<2>(waiting.back()));
        }
        if (!drinking.empty()) {
            double nans = t + (get<0>(drinking.back()) - pos - t * a) / b + get<1>(drinking.back());
            SMIN(get<2>(drinking.back()));
        }
        if (!done.empty()) {
            double nans = t + r + (get<0>(done.back()) - pos - t * a - r * b) / a + get<1>(done.back());
            SMIN(get<2>(done.back()));
        }
        assert(ansi != -2);
        optNext[i] = ansi;
        opt[i] = ans;
    }

    vi ret;
    int at = optNext[sz(P) - 1];
    while (at != -1) {
        ret.push_back(sz(P) - 2 - at);
        at = optNext[at];
    }
    ret.pop_back();
    cout << sz(ret) << endl;
    rep(i,0,sz(ret)) {
        if (i) cout << " ";
        cout << ret[i];
    }
    cout << endl;
    cerr << opt.back() - t - r << endl;
}
