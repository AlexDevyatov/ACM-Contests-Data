// Author: Johan Sannemo
// Copyright:
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void quadratic(double l, double a, double b, double t, double r, int n, vector<double> P) {
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

        for (int j = 0; j < i; ++j) {
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

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    double l, a, b, t, r;
    cin >> l >> a >> b >> t >> r;

    int n;
    cin >> n;

    vector<double> P(n);
    trav(it, P) cin >> it;
    
    if (n <= 30000) {
        quadratic(l, a, b, t, r, n, P);
        return 0;
    }

#define BEGIN -1
#define BUY_COFFEE(i) (3*i)
#define START_RUN(i) (3*i + 1)
#define END_RUN(i) (3*i + 2)
#define END (END_RUN(n - 1) + 1)
#define IS_BEGIN(x) ((x) == BEGIN)
#define IS_END(x) ((x) == END)
#define IS_BUY(x) (x%3 == 0)
#define IS_STARTRUN(x) (x%3 == 1)
#define IS_ENDRUN(x) (x%3 == 2)
    vector<pair<double, int>> events;
    events.emplace_back(0, BEGIN);
    rep(j,0,n) {
        events.emplace_back(P[j], BUY_COFFEE(j));
        events.emplace_back(P[j] + a * t, START_RUN(j));
        events.emplace_back(P[j] + a * t + b * r, END_RUN(j));
    }
    events.emplace_back(l, END);
    sort(all(events));
    double curt = 0;
    int lastBuy = -1;
    int isRunning = -1;
    double currentPos = 0;
    vi res;
    trav(it, events) {
        double newPos = it.first;
        curt += (newPos - currentPos) / ((isRunning >= 0) ? b : a);
        if (IS_BEGIN(it.second)) {}
        else if (IS_END(it.second)) { break; }
        else if (IS_BUY(it.second) && lastBuy == -1) { lastBuy = it.second / 3; res.push_back(lastBuy); }
        else if (IS_STARTRUN(it.second) && it.second / 3 == lastBuy) { isRunning = lastBuy; }
        else if (IS_ENDRUN(it.second) && it.second / 3 == isRunning) { isRunning = -1; lastBuy = -1; }
        currentPos = newPos;
    }
    cout << sz(res) << endl;
    trav(it, res) cout << it << " ";
    cout << endl;
    cerr << curt << endl;
}
