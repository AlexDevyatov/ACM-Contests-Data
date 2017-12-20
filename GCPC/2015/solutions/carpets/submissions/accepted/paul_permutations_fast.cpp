#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define sz(c) int((c).size())
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define xx first
#define yy second

struct entry {
	int xmin, xmax, ymin;
};

bool operator<(const entry &a, const entry &b) {
	return pii(a.ymin,a.xmin) < pii(b.ymin,b.xmin);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int W, H, c;
	cin >> W >> H >> c;
	vector<pii> tiles;
	FOR(i,0,c) {
		int a, wa, ha; cin >> a >> wa >> ha;
		FOR(j,0,a) tiles.push_back({wa,ha});
	}
	int n = sz(tiles);
	sort(begin(tiles),end(tiles));
	do {
		FOR(mask,0,1 << n) {
			FOR(i,0,n) if (mask & (1 << i)) swap(tiles[i].xx,tiles[i].yy);
			bool ok = true;
			set<entry> q;
			q.insert({0,W,0});
			FOR(i,0,n) {
				if (!sz(q)) break;
				entry e = *begin(q);
				q.erase(begin(q));
				while (sz(q) && begin(q)->ymin == e.ymin && begin(q)->xmin == e.xmax) {
					e.xmax = begin(q)->xmax;
					q.erase(begin(q));
				}
				if (e.xmax - e.xmin < tiles[i].xx || H - e.ymin < tiles[i].yy) {
					ok = false; break;
				}
				if (e.xmin + tiles[i].xx < e.xmax) {
					q.insert({e.xmin + tiles[i].xx,e.xmax,e.ymin});
				}
				if (e.ymin + tiles[i].yy < H) {
					q.insert({e.xmin,e.xmin + tiles[i].xx,e.ymin + tiles[i].yy});
				}
			}
			if (sz(q)) ok = false;
			if (ok) {
				cout << "yes" << endl;
				return 0;
			}
			FOR(i,0,n) if (mask & (1 << i)) swap(tiles[i].xx,tiles[i].yy);
		}
	} while (next_permutation(begin(tiles),end(tiles)));
	
	cout << "no" << endl;
}

