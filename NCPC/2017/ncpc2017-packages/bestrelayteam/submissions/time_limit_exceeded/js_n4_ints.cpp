#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Runner {
    string name;
    int a, b;
};

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<Runner> rs;
    rep(i,0,N) {
        Runner r;
        double a, b;
        cin >> r.name >> a >> b;
        r.a = int(100 * a + 0.5);
        r.b = int(100 * b + 0.5);
        rs.push_back(r);
    }
    random_shuffle(all(rs));
    int best = 10000;
    vi ans;
    rep(i,0,N) {
        int w = rs[i].a;
    rep(j,0,N) {
        if (i == j) continue;
        w += rs[j].b;
    rep(k,j+1,N) {
        if (i == k) continue;
        w += rs[k].b;
    rep(l,k+1,N) {
        if (i == l) continue;
        w += rs[l].b;
        if (w < best) {
            best = w;
            ans = vi {i, j, k, l};
        }
        w -= rs[l].b;
    }
        w -= rs[k].b;
    }
        w -= rs[j].b;
    }
    }
    cout << fixed << setprecision(2) << best / 100.0 << endl;
    trav(it, ans) {
        cout << rs[it].name << endl;
    }
}
