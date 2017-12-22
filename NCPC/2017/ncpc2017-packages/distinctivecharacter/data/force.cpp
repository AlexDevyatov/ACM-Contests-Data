#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int dist[1<<20];

int go(int k, const vi& has) {
    for (int b = 0; b < (1<<k); b++) {
        dist[b] = 999999999;
    }
	vector<int> q;
    trav(u, has) {
        dist[u] = 0;
        q.push_back(u);
    }
    int best;
    for (int i = 0; i < q.size(); i++) {
        int a = q[i];
        best = a;
        for (int j = 0; j < k; j++) {
            int b = a^(1<<j);
            if (dist[a]+1 < dist[b]) {
                dist[b] = dist[a]+1;
                q.push_back(b);
            }
        }
    }
    return dist[best];
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    srand(35235);

    int K = 20;
    int ans = rand() % (1 << K);

    vi rstr(200);
    trav(it, rstr) it = rand() % (1 << K);

    int curans = go(K, rstr);
    int wantans = curans + 1;
    vi nstr;
    trav(it, rstr) {
        if (__builtin_popcount(it ^ ans) >= wantans) nstr.push_back(it);
    }
    assert(go(K, nstr) == wantans);
    cout << sz(nstr) << " " << K << endl;
    trav(it, nstr) {
        for (int j = 0; j < K; j++) {
            if (it&(1<<j)) cout << "1";
            else cout << "0";
        }
        cout << endl;
    }
}
