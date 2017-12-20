#include <iostream>
#include <vector>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

vector<int> adj[2000];
int pred[2000], N, K, to;
bool mark[2000];

bool match(int n) {
	if (n == -1) return true;
	for (int to : adj[n]) {
		if (mark[to]) continue;
		mark[to] = true;
		if (match(pred[to])) {
			pred[to] = n;
			return true;
		}
	}
	return false;
}

int maxmatch() {
	fill_n(pred, 2000, -1);
	int ret = 0;
	FOR(i, 0, N) {
		fill_n(mark, 2000, false);
		if (match(i)) ret++;
	}
	return ret;
}

int main() {
	cin >> N;
	FOR(i, 0, N) {
		cin >> K;
		FOR(j, 0, K) {
			cin >> to;
			adj[i].push_back(to);
		}
	}
	cout << N-maxmatch() << endl;

	return 0;
}
