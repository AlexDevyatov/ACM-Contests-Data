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

// rather slow implementation, should still work

using namespace std;

struct Pirate {
	int x, y, v;
	vector<int> adj;
	bool visit;
};

struct Tentacle {
	int x, y;
	int match;
};

Tentacle T[105];
Pirate P[105];
Tentacle Head;
Pirate Cap;
double L[105][105];
vector<double> L2;
int N, M;

double timeBetween(Pirate p, Tentacle t) {
	return (sqrt((double)((p.x - t.x) * (p.x - t.x) + (p.y - t.y) * (p.y - t.y))) / (double)p.v);
}

bool aug(int v) {
	if (P[v].visit) return false;
	P[v].visit = true;
	for (int i = 0; i < P[v].adj.size(); i++) {
		int r = P[v].adj[i];
		if (T[r].match == -1 || aug(T[r].match)) {
			T[r].match = v;
			return true;
		}
	}
	return false;
}

void onerun() {
	cin >> N >> M;
	cin >> Cap.x >> Cap.y >> Cap.v;
	for (int i = 0; i < M; i++) cin >> P[i].x >> P[i].y >> P[i].v;
	cin >> Head.x >> Head.y;
	for (int i = 0; i < N; i++) cin >> T[i].x >> T[i].y;

	L2.clear();
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			L[i][j] = timeBetween(P[i], T[j]);
			L2.push_back(L[i][j]);
		}
	}

	sort(L2.begin(), L2.end());

	int x = -1;
	int y = L2.size();
	while (x + 1 < y) {
		int h = (x+y)/2;
		int Q = 0;
		for (int i = 0; i < M; i++) {
			P[i].adj.clear();
			for (int j = 0; j < N; j++) {
				if (L[i][j] <= L2[h]) P[i].adj.push_back(j);
			}
		}
		for (int i = 0; i < N; i++) T[i].match = -1;

		for (int i = 0; i < M; i++) {
			for (int i = 0; i < M; i++) P[i].visit = false;
			if (aug(i)) Q++;
		}

		if (Q == N) y = h;
		else x = h;
	}

	cout << setprecision(12) << (L2[y] + timeBetween(Cap, Head)) << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}