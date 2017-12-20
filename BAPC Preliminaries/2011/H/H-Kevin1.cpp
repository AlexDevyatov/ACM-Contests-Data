#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

struct State {
	int x, y;
	int t; // mod 8
};

State makeState(int x, int y, int t) {
	State s;
	s.x = x; s.y = y; s.t = t%8;
	return s;
}

int N, K;
bool safe[1005][1005][8];
bool done[1005][1005][8];
vector<State> Q;

bool isEndState(State s) {
	return (s.y == 2 * N + 1);
}

void onerun() {
	cin >> N >> K;
	int W = 2 * N + 1, H = 2 * N + 3;

	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			for (int t = 0; t < 8; t++) {
				if (x == 0 || y == 0 || x == W-1 || y == H-1) safe[x][y][t] = false;
				else safe[x][y][t] = (x%2 == 1 || y%2 == 0);
				done[x][y][t] = false;
			}
		}
	}

	for (int i = 0; i < K; i++) {
		int x, y, d;
		char dir;
		cin >> y >> x >> dir; y++;
		switch (dir) {
			case 'F': d = 0; break;
			case 'L': d = 6; break;
			case 'B': d = 4; break;
			case 'R': d = 2; break;
		}
		for (int x2 = 1; x2 < W - 1; x2++) {
			if (x2 <= x) {
				safe[x2][y][(2+d)%8] = false; safe[x2][y][(3+d)%8] = false;
			}
			if (x2 >= x) {
				safe[x2][y][(6+d)%8] = false; safe[x2][y][(7+d)%8] = false;
			}
		}
		for (int y2 = 2; y2 < H - 2; y2++) {
			if (y2 <= y) {
				safe[x][y2][d%8] = false; safe[x][y2][(1+d)%8] = false;
			}
			if (y2 >= y) {
				safe[x][y2][(4+d)%8] = false; safe[x][y2][(5+d)%8] = false;
			}
		}
	}

	Q.clear();
	int a = 0;
	for (int x = 1, b = 0; x < W; x += 2, b++) {
		Q.push_back(makeState(x, 1, 0));
		done[Q[b].x][Q[b].y][Q[b].t] = true;
	}

	State S[5];

	while (a < Q.size()) {
		State s = Q[a];
		if (isEndState(s)) {
			cout << "succeeds" << endl;
			return;
		}
		S[0] = makeState(s.x, s.y, s.t+1);
		S[1] = makeState(s.x+1, s.y, s.t+1);
		S[2] = makeState(s.x-1, s.y, s.t+1);
		S[3] = makeState(s.x, s.y+1, s.t+1);
		S[4] = makeState(s.x, s.y-1, s.t+1);
		for (int i = 0; i < 5; i++) {
			if (safe[S[i].x][S[i].y][S[i].t] && !done[S[i].x][S[i].y][S[i].t]) {
				done[S[i].x][S[i].y][S[i].t] = true;
				Q.push_back(S[i]);
			}
		}
		a++;
	}
	cout << "fails" << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}