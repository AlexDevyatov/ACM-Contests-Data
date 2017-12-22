// This solution is O*(n*3^k)
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

typedef pair<int,int> pii;
typedef set<pii> pq;
typedef vector<int> vi;

vi adj[120];
int neigh[120][120];

void discard(int V, vi &deg) {
	deg[V] = -1;
	for (int W: adj[V]) if (deg[W] > 0) --deg[W];
}

void take(int U, vi &deg) {
	deg[U] = -1;
	for (int V: adj[U]) if (deg[V] > 0) discard(V, deg);
}

vi nodes;

int solve(int i, vi deg, int goal) {
	if (goal == 0 || i < 0) return 0;

	int U = nodes[i];
	if (deg[U] == -1) return solve(i-1, deg, goal);

	vi ndeg = deg;
	take(U, ndeg);

	int val = 1+solve(i-1, ndeg, goal-1), rem = deg[U]-1;
	if (val >= goal) return val;

	for (int V: adj[U]) {
		if (deg[V] > 0 && rem > 0) {
			--rem;
			ndeg = deg;
			take(V, ndeg);
			val = max(val, 1+solve(i-1, ndeg, goal-1));
			if (val >= goal) return val;
			discard(V, deg);
		}
	}
	return val;
}

int seen[120];

void dfs(int u, vi &vis) {
	seen[u] = true;
	for (int v: adj[u]) if (!seen[v]) dfs(v, vis);
	vis.push_back(u);
}

int main(void) {
	int k, n;
	scanf("%d%d", &k, &n);
	if (n >= 5*(k-1)+1) {
		printf("possible\n");
		return 0;
	}
	vi deg(n+1);
	for (int i = 1; i <= n; ++i) {
		int d;
		scanf("%d", &d);
		for (int j= 0; j < d; ++j) {
			int a;
			scanf("%d", &a);
			adj[i].push_back(a);
		}
		deg[i] = d;
	}
	int ms = 0;
	memset(seen, 0, sizeof(seen));
	for (int i = 1; i <= n; ++i) {
		if (!seen[i]) {
			nodes.clear();
			dfs(i, nodes);
			ms += solve(nodes.size()-1, deg, k-ms);
		}
	}
	printf("%spossible\n", ms >= k ? "" : "im");
	return 0;
}
