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

struct Edge {
	int v;
	int L;
	bool sentry;
};

struct Node {
	int dist;
	int parent;
	vector<Edge> adj;
	void changeWeight(int v, int L) {
		for (int i = 0; i < adj.size(); i++) if (adj[i].v == v) adj[i].L = L;
	}
	bool sentry(int v) {
		for (int i = 0; i < adj.size(); i++) if (adj[i].v == v) return adj[i].sentry;
		return false;
	}
};

struct NodeDist {
	int v;
	int dist;
	bool operator<(const NodeDist& r) const {
		return (r.dist < dist);
	}
};

NodeDist makeND(int v, int D) {
	NodeDist nd;
	nd.v = v; nd.dist = D;
	return nd;
}

Edge makeEdge(int v, int L, bool sentry = false) {
	Edge e;
	e.v = v; e.L = L; e.sentry = sentry;
	return e;
}

Node V[1105];
int N, N2, M, S;
priority_queue<NodeDist> Q;

void Dijkstra() {
	while (!Q.empty()) Q.pop();
	V[0].dist = 0;
	Q.push(makeND(0, 0));
	while (!Q.empty()) {
		NodeDist nd = Q.top(); Q.pop();
		if (nd.dist > V[nd.v].dist) continue;
		for (int i = 0; i < V[nd.v].adj.size(); i++) {
			Edge e = V[nd.v].adj[i];
			if (e.L == INT_MAX) continue;
			if (nd.dist + e.L < V[e.v].dist) {
				V[e.v].dist = nd.dist + e.L;
				V[e.v].parent = nd.v;
				Q.push(makeND(e.v, V[e.v].dist));
			}
		}
	}
}

void onerun() {
	cin >> N >> M;
	for (int i = 0; i < N + 100; i++) {
		V[i].adj.clear(); V[i].dist = INT_MAX; V[i].parent = -1;
	}
	for (int i = 0; i < M; i++) {
		int a, b, l;
		cin >> a >> b >> l; a--; b--;
		V[a].adj.push_back(makeEdge(b, l));
		V[b].adj.push_back(makeEdge(a, l));
	}
	cin >> S;
	N2 = N;
	for (int i = 0; i < S; i++) {
		int x;
		cin >> x; x--;
		V[N2].adj = V[x].adj; V[N2].dist = INT_MAX; V[N2].parent = -1;
		V[x].adj.clear(); V[x].adj.push_back(makeEdge(N2, 0, true)); V[N2++].adj.push_back(makeEdge(x, 0, true));
	}
	
	int T = 0;
	Dijkstra();
	T += 2 * V[N-1].dist;
	for (int i = 0; i < N2; i++) {
		for (int j = 0; j < V[i].adj.size(); j++) {
			V[i].adj[j].L += V[i].dist - V[V[i].adj[j].v].dist;
		}
	}
	int v = N - 1;
	while (v != 0) {
		int v2 = V[v].parent;
		if (V[v2].sentry(v)) {
			V[v2].changeWeight(v, INT_MAX);
			V[v].changeWeight(v2, 0);
		}
		else V[v].adj.push_back(makeEdge(v2, 0));
		v = v2;
	}
	for (int i = 0; i < N2; i++) {
		V[i].dist = INT_MAX; V[i].parent = -1;
	}
	Dijkstra();

	if (V[N-1].dist == INT_MAX) cout << "No safe route" << endl;
	else {
		T += V[N-1].dist;
		cout << T << endl;
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}