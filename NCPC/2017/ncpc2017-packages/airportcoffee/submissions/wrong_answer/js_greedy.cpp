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

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    double l, a, b, t, r;
    cin >> l >> a >> b >> t >> r;

    int n;
    cin >> n;

    vector<double> P(n);
    trav(it, P) cin >> it;

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
