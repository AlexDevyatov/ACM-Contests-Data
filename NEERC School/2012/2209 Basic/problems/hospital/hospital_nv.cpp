#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

struct edge
{
	int a, b;
	long long l, r;
	edge() {};
	edge(int a, int b): a(a), b(b), l(0), r(0) {};
};

void swap(edge& e)
{
	std::swap(e.a, e.b);
	std::swap(e.l, e.r);
}

long long all_weight = 0;
vector< vector<int> > g;
vector<edge> edges;
vector<bool> used;
vector<long long> w;

long long dfs(int v)
{
	used[v] = true;
	long long res = w[v];
	for (int i = 0; i < g[v].size(); i++)
	{
		int t = g[v][i];
		if (edges[t].a != v) swap(edges[t]);
		int u = edges[t].b;
		if (used[u]) continue;
		long long cur_w = dfs(u);
		edges[t].l = cur_w;
		edges[t].r = all_weight - cur_w;
		res += cur_w;
	}
	return res;
}

int main()
{
	freopen("hospital.in", "r", stdin);
	freopen("hospital.out", "w", stdout);
	int n;
	cin >> n;
	g.resize(n);
	used.resize(n);
	w.resize(n);
    edges.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> w[i];
		all_weight += w[i];
	}
	for (int i = 0; i < n - 1; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(i);
		g[b].push_back(i);
		edges[i] = edge(a, b);
	}
	dfs(0);
	long long ans = 1e18;
	int pos = -1;
	for (int v = 0; v < n; v++)
	{
		long long cur_ans = -1;
		for (int i = 0; i < g[v].size(); i++)
		{
			int t = g[v][i];
			if (edges[t].a != v) swap(edges[t]);
			cur_ans = max(cur_ans, edges[t].r);
		}
		if (cur_ans < ans)
		{
			ans = cur_ans;
			pos = v;
		}
	}
	cout << pos + 1 << endl;
}