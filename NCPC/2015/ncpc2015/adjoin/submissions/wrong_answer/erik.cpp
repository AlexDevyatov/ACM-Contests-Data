#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#define rep(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int n_v, n_e;
int comp[10000];

ostream& operator<<(ostream& os, const vi&v) {
	rep(i,0,v.size())
		os << v[i] << ' ';
	return os;
}

int dist(const vi&r, const vi&s) {
	int k = 0; while(k < r.size() && k < s.size() && r[k] == s[k]) ++k;
	return r.size() + s.size() - 2*k;
}

bool rev(const int&a, const int&b) {
	return a > b;
}

int main() {
	scanf("%d%d", &n_v, &n_e);
	vvi adj(n_v, vi(0));
	vvi id(n_v, vi(0));
	vvi trees;
	vi tree_roots;
	for(int i = 0; i < n_e; ++i) {
		int a,b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i = 0; i < n_v; ++i)
		comp[i] = -1;
	int n_t = 0;
	for(int i = 0; i < n_v; ++i) {
		if(comp[i] == -1) {
			vi T;
			tree_roots.push_back(i);
			comp[i] = n_t++;	
			queue<int> q;
			q.push(i);
			while(q.size()) {
				int u = q.front(); q.pop();
				T.push_back(u);
				int ct = 0;
				for(int j = 0; j < adj[u].size(); ++j) {
					int v = adj[u][j];
					if(comp[v] == -1) {
						comp[v] = comp[u];
						id[v] = id[u]; id[v].push_back(ct++);
						q.push(v);
					}
				}	
			}
			trees.push_back(T);
		}
	}
	
	vi maxdist(n_v, 0);
	vi mindist(n_t, 10000);
	rep(i,0,n_t) {
		rep(j,0,trees[i].size()) {
			int u = trees[i][j];
			rep(k,0,trees[i].size()) {
				int v = trees[i][k];
				maxdist[u] = max(maxdist[u], dist(id[u], id[v]));
			}
			mindist[i] = min(mindist[i], maxdist[u]);
		}
	}

	sort(mindist.begin(), mindist.end(), rev);
	
	int ans = 0;
	rep(i,0,n_t) {
		rep(j,0,n_t) {
			ans = max(ans, 2 + mindist[i] + mindist[j] - int(i == j) - int(i == 0) - int(j == 0) + int(i == 0 && j == 0));
		}
	}
	cout << ans << endl;
	return 0;
}
