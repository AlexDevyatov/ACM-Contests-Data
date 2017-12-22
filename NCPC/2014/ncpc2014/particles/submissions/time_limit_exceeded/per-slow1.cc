#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

vi adj[600];
double dist[600][600];

int st[600][600];
double ans[250000];
int mate[250000];

int par[250000], ht[250000];
vi children[250000];

int get_head(int i) {
	return par[i] == i ? i : get_head(par[i]);
}

bool same(int i, int j) { return get_head(i) == get_head(j); }

int join(int i, int j) {
	int a = get_head(i), b = get_head(j);
	int r = -1;
	if (a != b) {
		r = a;
		if (ht[a] <= ht[b]) {
			par[a] = b;
			children[b].push_back(a);
		}
		else {
			par[b] = a;
			children[a].push_back(b);
		}
		if (ht[a] == ht[b]) ++ht[b];
	}
	return r;
}

void search(int r, double d) {
	if (r == -1) return;
	if (same(r, mate[r])) ans[r] = ans[mate[r]] = max(d, ans[r]);
	for (auto c: children[r])
		search(c, d);
}

double sqr(double x) {return x*x; }

typedef tuple<double, int, int> state;

int main(void) {
	int n, m;
	scanf("%d", &n);
	int x[600], y[600];
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", x+i, y+i);
	for (int i = 1;i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			dist[i][j] = sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<state> S;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			S.push_back(state(dist[i][j], i, j));
		}
	int N = S.size();
	sort(S.begin(), S.end());
	for (int a = 0; a < N; ++a) {
		st[get<1>(S[a])][get<2>(S[a])] = a;
		//		printf("%d: %d %d %lf\n", a, get<1>(S[a]),get<2>(S[a]),get<0>(S[a]));
	}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (i == j) continue;
			mate[st[i][j]] = st[j][i];
		}
	for (int i = 0; i < N; ++i)
		par[i] = i, ht[i] = 0;
	for (int at = N-1; at >= 0; --at) {
		double d = get<0>(S[at]);
		int u = get<1>(S[at]);
		int v = get<2>(S[at]);
		for (int w: adj[u]) {
			if (dist[w][v] >= d) {
				search(join(at, st[w][v]), d);
			}
		}
		for (int w: adj[v]) {
			if (dist[u][w] >= d) {
				search(join(at, st[u][w]), d);
			}
		}
	}

	int l;
	scanf("%d", &l);
	for (int i = 0; i < l; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%.9lf\n", ans[st[a][b]]);
	}
	
	return 0;
}
