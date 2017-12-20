#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int carpets[20][2], W, H, C, c, a, w, h, used[20], usedC, possArea;
bool floo[100][100];

bool bt(int carpet, int x, int y, int occ) {
	if (occ == W*H) return true;
	if (carpet >= C) return false;
	if (x >= W) return bt(carpet, 0, y+1, occ); // no check with y necessary
	if (floo[x][y]) return bt(carpet, x+1, y, occ); // search for first free
	FOR(rot, 0, 2) {
		int cur = used[carpet];
		if (x + carpets[cur][rot] > W || y + carpets[cur][1-rot] > H) continue;
		bool allFree = true;
		FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) if (floo[x+i][y+j]) allFree = false;
		if (allFree) {
			FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) floo[x+i][y+j] = true;
		       	if (bt(carpet + 1, x+carpets[cur][rot], y, occ + carpets[cur][0]*carpets[cur][1])) return true;
			FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) floo[x+i][y+j] = false;
		}
	}
	return false;
}

int main() {
	cin >> W >> H >> c;
	int sum = 0;
	FOR(i, 0, c) {
		cin >> a >> w >> h;
		FOR(j, 0, a) {
			carpets[C][0] = w;
			carpets[C][1] = h;
			used[C] = C;
			C++;
			sum+=w*h;
		}
	}
	cerr << sum << " vs " << W*H << endl;
	do {
		memset(floo, 0, sizeof(floo));
		if (bt(0,0,0,0)) {
			cout << "yes" << endl;
			return 0;
		}
	} while (next_permutation(used, used + C));
	cout << "no" << endl;

	return 0;
}
