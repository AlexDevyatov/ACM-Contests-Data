#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <climits>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int N, P, M, G, T, p[16], t[16], s, d, cost, dist[16][20000], m[16][16], opt[65536][16], pow2[17];
vector<int> adjList[20000], costList[20000];

bool solve() {
	FOR(i, 0, pow2[P]) fill_n(opt[i], P, INT_MAX);
	opt[1][0] = 0;
	FOR(i, 1, pow2[P]) FOR(j, 0, P) {
		if (opt[i][j] == INT_MAX) continue;
		FOR(k, 0, P) {
			if ((i >> k) & 1 || m[j][k] == INT_MAX) continue;
			opt[i + pow2[k]][k] = min(opt[i + pow2[k]][k], opt[i][j] + m[j][k]);
		}
	}
	int len = opt[pow2[P]-1][0];
	FOR(i, 1, P) {
		if (opt[pow2[P]-1][i] == INT_MAX || m[i][0] == INT_MAX) continue;
		len = min(len, opt[pow2[P]-1][i] + m[i][0]);
	}
	return len <= G;
}

int main() {
	cin >> N >> P >> M >> G >> T;
	FOR(i, 1, P+1) cin >> p[i] >> t[i];
	P++; // p[0] = t[0] = 0 is implicitely set
	FOR(i, 0, M) {
		cin >> s >> d >> cost;
		adjList[s].push_back(d);
		costList[s].push_back(cost);
		adjList[d].push_back(s);
		costList[d].push_back(cost);
	}
	FOR(i, 0, P) {
		G -= t[i];
		fill_n(dist[i], N, INT_MAX);
		dist[i][p[i]] = 0;
		set<pair<int,int> > pq;
		pq.insert(make_pair(0, p[i]));
		while (!pq.empty()) {
			int cur = pq.begin()->second;
			pq.erase(pq.begin());
			for (unsigned int j = 0; j < adjList[cur].size(); j++) {
				if (dist[i][cur] + costList[cur][j] >= dist[i][adjList[cur][j]]) continue;
				if (dist[i][adjList[cur][j]] < INT_MAX) pq.erase(pq.find(make_pair(dist[i][adjList[cur][j]], adjList[cur][j])));
				dist[i][adjList[cur][j]] = dist[i][cur] + costList[cur][j];
				pq.insert(make_pair(dist[i][adjList[cur][j]], adjList[cur][j]));
			}
		}
		FOR(j, 0, P) m[i][j] = dist[i][p[j]];
	}
	pow2[0] = 1;
	FOR(i, 1, P+1) pow2[i] = 2 * pow2[i-1];
	if (solve()) {
		cout << "possible without taxi" << endl;
		return 0;
	} else FOR(i, 0, P) FOR(j, i+1, P) {
		if (m[i][j] <= T) continue;
		int old = m[i][j];
		m[i][j] = T;
		if (solve()) {
			cout << "possible with taxi" << endl;
			return 0;
		}
		m[i][j] = old;
	}
	cout << "impossible" << endl;

	return 0;
}
