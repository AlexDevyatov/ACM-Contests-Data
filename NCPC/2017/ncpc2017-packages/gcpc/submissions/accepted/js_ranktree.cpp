#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template <class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
	  tree_order_statistics_node_update>;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    Tree<pair<pii, int>> tr;
    vector<pii> cur(N);
    rep(i,0,N) tr.insert(make_pair(pii(0, 0), i));
    rep(i,0,M) {
        int t, p;
        cin >> t >> p;
        --t;

        pii now = cur[t];

        pii nx = now;
        nx.first--;
        nx.second += p;

        tr.erase(make_pair(now, t));
        tr.insert(make_pair(nx, t));

        cur[t] = nx;
        cout << tr.order_of_key(make_pair(cur[0], 0)) + 1 << endl;
    }
}
