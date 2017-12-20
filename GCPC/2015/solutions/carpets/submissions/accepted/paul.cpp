#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define sz(c) int((c).size())
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define xx first
#define yy second

int n = 0, mask;
int W, H, w[8], h[8];

bool rec(vector<pii> state) {
	if (sz(state) == 1) return true;
	
	int j = 0;
	FOR(i,1,sz(state)) if (state[i].yy > state[j].yy) j = i;
	FOR(i,0,n) if (mask & (1 << i)) {
		FOR(k,0,2) {
			swap(w[i],h[i]);
			if (state[j].yy < h[i] || state[j+1].xx - state[j].xx < w[i]) continue;
			vector<pii> nstate = state;
			if (w[i] < state[j+1].xx - state[j].xx) {
				pii p(nstate[j].xx+w[i],nstate[j].yy);
				nstate.insert(begin(nstate)+j+1,p);
			}
			nstate[j].yy -= h[i];
			FOR(i,0,sz(nstate)-1) {
				while (i < sz(nstate)-1 && nstate[i].yy == nstate[i+1].yy)
					nstate.erase(begin(nstate)+i+1);
			}

			mask ^= 1 << i;
			if (rec(nstate)) return true;		
			mask ^= 1 << i;
		}
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> W >> H;
	int c; cin >> c;
	FOR(i,0,c) {
		int a, wa, ha; cin >> a >> wa >> ha;
		FOR(j,0,a) w[n] = wa, h[n] = ha, n++;
	}
	mask = (1 << n) - 1;
	vector<pii> state = {{0,H},{W,0}};
	if (!rec(state)) cout << "no\n";
        else cout << "yes\n";
}

