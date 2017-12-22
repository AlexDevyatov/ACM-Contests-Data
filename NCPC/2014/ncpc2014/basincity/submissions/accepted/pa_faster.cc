// This solution is O*[(1+sqrt(2))^k] ~ O*(2.42^k)
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
int activedeg[120];

void discard(int V, pq &degq, vi &deg) {
	degq.erase(pii(deg[V], V));
	deg[V] = -1;
	for (int W: adj[V]) {
		if (deg[W] > 0) {
			degq.erase(pii(deg[W], W));
			--deg[W];
			degq.insert(pii(deg[W], W));
		}
	}
}

void take(int U, pq &degq, vi &deg) {
	degq.erase(pii(deg[U], U));
	deg[U] = -1;
	for (int V: adj[U]) {
		if (deg[V] > 0) {
			discard(V, degq, deg);
		}
	}
}

int solve(pq degq, vi deg, int goal) {
	if (goal == 0 || degq.empty()) return 0;

	int U = degq.begin()->second;
	pq nq = degq;
	vi ndeg = deg;

	take(U, nq, ndeg);

	int val = 1+solve(nq, ndeg, goal-1);
	if (val >= goal || deg[U] <= 1) return val;

	nq = degq;
	ndeg = deg;
	int seen = 0, udeg = deg[U], taken = 0;
	for (int V: adj[U]) {
		if (ndeg[V] >= 0) {
			++seen;
			++taken;
			take(V, nq, ndeg);
			if (seen < udeg-1) {
				val = max(val, solve(nq, ndeg, goal-1)+1);
				if (val >= goal) return val;
				discard(V, degq, deg);
				taken = 0;
				nq = degq;
				ndeg = deg;
			} 
		}
	}
	if (taken == 2) val = max(val, 2+solve(nq, ndeg, goal-2));
	return val;
}

int seen[120];

void dfs(int u, pq &active) {
	active.insert(pii(adj[u].size(), u));
	seen[u] = true;
	for (int v: adj[u]) if (!seen[v]) dfs(v, active);
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
			pq active;
			dfs(i, active);
			int sz = solve(active, deg, k-ms);
			ms += sz;
		}
	}
	printf("%spossible\n", ms >= k ? "" : "im");
	return 0;
}