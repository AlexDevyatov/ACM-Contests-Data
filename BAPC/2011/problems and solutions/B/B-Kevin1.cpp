#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

struct State {
	int x, y, t;
	bool operator<(const State& r) const {
		return (r.t < t);
	}
};

State makeState(int x, int y, int t) {
	State s;
	s.x = x; s.y = y; s.t = t;
	return s;
}

int H, W, D;

int map[505][505];
int T[505][505];
int sx, sy;
priority_queue<State> Q;

void onerun() {
	cin >> H >> W >> D;
	for (int i = 0; i <= W+1; i++) for (int j = 0; j <= H+1; j++) {
		map[i][j] = 0; T[i][j] = INT_MAX;
	}
	for (int j = 1; j <= H; j++) {
		string s;
		cin >> s;
		for (int i = 1; i <= W; i++) {
			switch (s[i-1]) {
				case 'S': map[i][j] = 0; sx = i; sy = j; break;
				case '.': map[i][j] = 0; break;
				case '#': map[i][j] = -1; break;
				case '@': map[i][j] = 1; break;
			}
		}
	}

	while (!Q.empty()) Q.pop();
	Q.push(makeState(sx, sy, 0));
	State S[4];

	while (!Q.empty()) {
		State s = Q.top(); Q.pop();
		if (s.t > T[s.x][s.y]) continue;
		if (s.x == 0 || s.y == 0 || s.x == W+1 || s.y == H+1) {
			cout << s.t << endl;
			break;
		}
		S[0] = makeState(s.x+1, s.y, s.t+1);
		S[1] = makeState(s.x-1, s.y, s.t+1);
		S[2] = makeState(s.x, s.y+1, s.t+1);
		S[3] = makeState(s.x, s.y-1, s.t+1);
		for (int i = 0; i < 4; i++) {
			if (map[S[i].x][S[i].y] < 0) continue;
			S[i].t += map[S[i].x][S[i].y] * D;
			if (S[i].t < T[S[i].x][S[i].y]) {
				T[S[i].x][S[i].y] = S[i].t;
				Q.push(S[i]);
			}
		}
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}
