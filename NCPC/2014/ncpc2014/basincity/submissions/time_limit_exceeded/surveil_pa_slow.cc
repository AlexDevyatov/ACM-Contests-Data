// Initial unoptimized version O*(4^k) time complexity, worst case is
// disjoint collection of 5-cliques
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

typedef pair<int,int> pii;
typedef set<pii> pq;
typedef vector<int> vi;

vi adj[100];
int neigh[100][100];
int activedeg[100];

void take(int U, pq &degq, vi &deg) {
	degq.erase(pii(deg[U], U));
	deg[U] = -1;
	for (int V: adj[U]) {
		if (deg[V] > 0) {
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
	}
}

bool solve(const pq &degq, const vi &deg, int goal) {
	if (goal == 0) return true;
	if (degq.empty()) return false;

	pq nq = degq;
	vi ndeg = deg;
	pii rem = *nq.begin();
	int U = rem.second;

	take(U, nq, ndeg);
	//	printf("goal %d U %d (deg %d %d) take it\n", goal, U, deg[U], rem.first);
	if (solve(nq, ndeg, goal-1)) return true;
	//	printf("goal %d U %d (deg %d) don't take it\n", goal, U, deg[U]);

	nq = degq;
	ndeg = deg;

	if (deg[U] == 1) return false;

	if (deg[U] == 2) {
		int t = 0;
		for (int V: adj[U]) {
			if (ndeg[V] > 0) {
				++t;
				take(V, nq, ndeg);
			}
		}
		return t == 2 && solve(nq, ndeg, goal-2);
	}

	// deg = 3 or 4 (mostly 3)
	int seen = 0;
	for (int V: adj[U]) {
		if (ndeg[V] > 0 && seen < deg[U]-1) {
			++seen;
			take(V, nq, ndeg);
			if (solve(nq, ndeg, goal-1)) return true;
			nq = degq;
			ndeg = deg;
		}
	}
	return false;
}

int main(void) {
	int k, n;
	scanf("%d%d", &k, &n);
	if (n >= 5*(k-1)+1) {
		printf("possible\n");
		return 0;
	}
	// n <= 51
	pq active;
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
		active.insert(pii(d, i));
	}
	printf("%spossible\n", solve(active, deg, k) ? "" : "im");
	return 0;
}
