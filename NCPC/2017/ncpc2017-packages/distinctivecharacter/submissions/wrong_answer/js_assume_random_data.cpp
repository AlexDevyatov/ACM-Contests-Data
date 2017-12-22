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
    srand(123);
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    bool covered = n * k / 2 >= (1 << k);
    if (covered) {
        set<string> has;
        rep(i,0,n) {
            string s;
            cin >> s;
            has.insert(s);
        }
        rep(i,0,1<<k) {
            string s;
            rep(j,0,k) if (i & (1 << j)) s.push_back('1'); else s.push_back('0');
            if (!has.count(s)) {
                cout << s << endl;
                return 0;
            }
        }
        rep(i,0,k) cout << 0;
        cout << endl;
    } else {
        vi has(n);
        rep(i,0,n) {
            int w = 0;
            string s;
            cin >> s;
            rep(j,0,k) w = (w << 1) | (s[j] == '1');
            has[i] = w;
        }
        int best = 0;
        int w = 0;
        rep(i,0,100000000 / n) {
            int num = rand() % (1 << k);
            int dist = 1000;
            trav(it, has) dist = min(dist, __builtin_popcount(it ^ num));
            if (dist > best) {
                best = dist;
                w = num;
            }
        }
        for (int i = k - 1; i >= 0; --i) {
            cout << ((w & (1 << i)) >> i);
        }
        cout << endl;
    }
}
