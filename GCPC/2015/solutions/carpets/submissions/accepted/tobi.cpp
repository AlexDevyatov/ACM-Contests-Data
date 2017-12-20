#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int carpets[20][2], W, H, C, c, a, w, h, used[20], usedC, possArea;
bool floo[100][100];

bool bt(int carpet, int x, int y) {
	if (carpet >= usedC) return true; // no further fit check necessary
	if (x >= W) return bt(carpet, 0, y+1); // no check with y necessary
	if (floo[x][y]) return bt(carpet, x+1, y); // search for first free
	FOR(rot, 0, 2) {
		int cur = used[carpet];
		if (x + carpets[cur][rot] > W || y + carpets[cur][1-rot] > H) continue;
		bool allFree = true;
		FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) if (floo[x+i][y+j]) allFree = false;
		if (allFree) {
			FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) floo[x+i][y+j] = true;
		       	if (bt(carpet + 1, x+carpets[cur][rot], y)) return true;
			FOR(i, 0, carpets[cur][rot]) FOR(j, 0, carpets[cur][1-rot]) floo[x+i][y+j] = false;
		}
	}
	return false;
}

int main() {
	cin >> W >> H >> c;
	FOR(i, 0, c) {
		cin >> a >> w >> h;
		FOR(j, 0, a) {
			carpets[C][0] = w;
			carpets[C][1] = h;
			C++;
		}
	}
	FOR(i, 1, (1<<C)) {
		usedC = possArea = 0;
		FOR(j, 0, C) if ((1 << j) & i) {
			used[usedC++] = j;
			possArea += carpets[j][0] * carpets[j][1];
		}
		if (possArea != W*H) continue;
		do {
			memset(floo, 0, sizeof(floo));
			if (bt(0,0,0)) {
				cout << "yes" << endl;
				return 0;
			}
		} while (next_permutation(used, used + usedC));
	}
	cout << "no" << endl;

	return 0;
}
