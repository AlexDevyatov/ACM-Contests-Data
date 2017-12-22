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
    rep(i,1,sz(P)) {
        double pos = P[i];
        // Pop away everything in the queues that are too far away

        double waitingEndPos = pos + t * a;
        double drinkingEndPos = pos + t * a + r * b;

        pair<double, int> ret(1e100, -2);

        for (int j = max(0, i - 6000); j < i; ++j) {
            double p = P[j];
            if (p < waitingEndPos) ret = min(ret, make_pair( (p - pos) / a + opt[j], j ));
            else if (p < drinkingEndPos) ret = min(ret, make_pair( (p - pos - t * a) / b + t + opt[j], j ));
            else ret =  min(ret, make_pair( (p - pos - t * a - r * b) / a + t + r + opt[j], j ));
        }
        cerr << "best at " << i << " is " << ret.second << " tot " << ret.first << endl;
        assert(ret.second != -2);
        optNext[i] = ret.second;
        opt[i] = ret.first;
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
