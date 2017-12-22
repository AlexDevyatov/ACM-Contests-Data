#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1<<20];
int val[1<<20], seen[1<<20];

void dfs(int u, int &v, int &e) {
  if (seen[u]) return;
  seen[u] = true;
  ++v;
  e += adj[u].size();
  for (auto x: adj[u])
    dfs(x, v, e);
}

int main(void) {
  int n, v = 0;
  scanf("%d", &n);
  unordered_map<int, int> idx;
  for (int i = 0; i < n; ++i) {
    int s, t;
    scanf("%d%d", &s, &t);
    int &si = idx[s], &ti = idx[t];
    if (!si) val[si = ++v] = s;
    if (!ti) val[ti = ++v] = t;
    adj[si].push_back(ti);
    adj[ti].push_back(si);
  }
  memset(seen, 0, sizeof(seen));
  for (int i = 1; i <= v; ++i) {
    if (!seen[i]) {
      int v = 0, e = 0;
      dfs(i, v, e);
      assert(e % 2 == 0);
      assert(e/2 <= v);
    }
  }
  return 42;
}
