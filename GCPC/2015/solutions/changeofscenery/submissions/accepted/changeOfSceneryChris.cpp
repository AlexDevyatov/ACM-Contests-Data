/*
 *	Author: Christian Müller, TUM
 */
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

using namespace std;

struct edge {
	int to;
	int cost;
};
struct node {
	vector<edge> edges;
};
struct dijk{
	int node;
	int dist;
    bool operator<(const dijk& rhs) const
    {
        return dist < rhs.dist;
    }
    bool operator>(const dijk& rhs) const
    {
        return dist > rhs.dist;
    }
};

void dijkstra(vector<node>& graph, int start, int n, int* prevs, int* dists, bool* multi) {

	bool visited[n];
	for (int i = 0; i < n; i++) {
		dists[i] = INT_MAX;
		visited[i] = false;
		multi[i] = false;
	}
	dists[start] = 0;

	priority_queue<dijk, vector<dijk>, greater<dijk> > q;
	q.push(dijk { start, 0 });

	while(!q.empty()) {
		dijk d = q.top();
		q.pop();
		if (visited[d.node]) {
			continue;
		}
		visited[d.node] = true;

		for (auto& e : graph[d.node].edges) {
			if (dists[d.node] != INT_MAX && dists[e.to] > dists[d.node] + e.cost) {
				prevs[e.to] = d.node;
				dists[e.to] = dists[d.node] + e.cost;
				q.push(dijk { e.to, dists[e.to] });
				multi[e.to] = multi[d.node];
			} else if (dists[d.node] != INT_MAX && dists[e.to] == dists[d.node] + e.cost) {
				multi[e.to] = true;
			}
		}
	}
}

int main(int argc, char **argv) {
		int n, m ,k;
		cin >> n >> m >> k;
		cin.ignore();

		for (int i = 0; i < k; i++) {
			int junction;
			cin >> junction;
			// ignore
		}
		vector<node> graph;
		for (int i = 0; i < n; i++) {
			graph.push_back(node());
		}
		for (int i = 0; i < m; i++) {
			int from, to, length;
			cin >> from >> to >> length;
			from--;
			to--;
			if (from != to) {
				graph[from].edges.push_back(edge { to, length });
				graph[to].edges.push_back(edge { from, length });
			}
		}
		int startprevs[n];
		int startdists[n];
		bool multi[n];

		dijkstra(graph, 0, n, startprevs, startdists, multi);

		cout << (multi[n-1] ? "yes":"no") << endl;
}


