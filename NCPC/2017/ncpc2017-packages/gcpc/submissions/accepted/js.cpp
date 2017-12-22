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

    int N, M;
    cin >> N >> M;

    vector<pii> cur(N);
    set<pair<pii, int>> sc;
    rep(i,0,N) sc.emplace(pii(0, 0), i);
    int rank = 0;
    rep(i,0,M) {
        int t, p;
        cin >> t >> p;
        --t;

        pii now = cur[t];

        pii nx = now;
        nx.first--;
        nx.second += p;
        if (t != 0) {
            if (now >= cur[0] && nx < cur[0]) ++rank;
        } else {
            auto it = sc.find(make_pair(now, t));
            auto until = sc.lower_bound(make_pair(nx, t));
            while (it != until) {
                --it;
                --rank;
            }
        }

        sc.erase(make_pair(now, t));
        sc.emplace(nx, t);
        cur[t] = nx;
        cout << rank + 1 << endl;
    }
}
