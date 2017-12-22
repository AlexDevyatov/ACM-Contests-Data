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

template <class T>
struct SubMatrix {
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>>& v) {
		int R = sz(v), C = sz(v[0]);
		p.assign(R+1, vector<T>(C+1));
		rep(r,0,R) rep(c,0,C)
			p[r+1][c+1] = v[r][c] + p[r][c+1] + p[r+1][c] - p[r][c];
	}
	T sum(int u, int l, int d, int r) {
		return p[d][r] - p[d][l] - p[u][r] + p[u][l];
	}
};

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<Runner> rs;

    vector<vector<int>> m(1200, vector<int>(1200));
    rep(i,0,N) {
        Runner r;
        double a, b;
        cin >> r.name >> a >> b;
        r.a = int(100 * a + 0.5);
        r.b = int(100 * b + 0.5);
        m[r.a - 800][r.b - 800]++;
        rs.push_back(r);
    }
    SubMatrix<int> sm(m);

    vector<Runner> nrs;
    trav(it, rs) {
        if (sm.sum(0, 0, it.a - 800, it.b - 800) < 4) nrs.push_back(it);
    }
    rs = nrs;
    N = sz(rs);
    int best = 10000;
    vi ans;
    rep(i,0,N) {
    rep(j,0,N) {
        if (i == j) continue;
    rep(k,j+1,N) {
        if (i == k) continue;
    rep(l,k+1,N) {
        if (i == l) continue;
        int w = rs[i].a + rs[j].b + rs[k].b + rs[l].b;
        if (w < best) {
            best = w;
            ans = vi {i, j, k, l};
        }
    }
    }
    }
    }
    cout << fixed << setprecision(2) << best / 100.0 << endl;
    trav(it, ans) {
        cout << rs[it].name << endl;
    }
}
