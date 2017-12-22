#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const bool DEBUG=false;
int cookie = 0;


vector<int> adj[1<<20];
int val[1<<20];
int mate[1<<20];
int seen[1<<20];

void match(int a, int b) {
  assert(mate[a] == -1);
  assert(mate[b] == -1);
  mate[a] = b;
  mate[b] = a;
}

void unmatch(int v) {
  if (mate[v] != -1) {
    mate[mate[v]] = -1;
    mate[v] = -1;
  }
}

bool extend(int v, int c) {
  if (seen[v] == c) return false;
  seen[v] = c;
  for (auto x: adj[v]) {
    if (mate[x] == -1 || extend(mate[x], c)) {
      unmatch(v);
      match(v, x);
      return true;
    }
  }
  return false;
}


bool improve(int v, int c, ll delta) {
  //  printf("improve? %d %lld\n", v, delta);
  if (seen[v] == c) return false;
  seen[v] = c;
  int other = mate[v] == adj[v][0] ? adj[v][1] : adj[v][0];
  delta += val[mate[v]] - val[other];
  if (mate[other] == -1 && delta <= 0) return false;
  if (mate[other] == -1 || improve(mate[other], c, delta)) {
    unmatch(v);
    match(v, other);
    return true;
  }
  return false;
}

int main(void) {
  int n, v;
  scanf("%d", &n);
  v = n;
  map<int, int> idx;
  for (int i = 0; i < n; ++i) {
    int s, t;
    scanf("%d%d", &s, &t);
    int &si = idx[s], &ti = idx[t];
    if (!si) val[si = v++] = s;
    if (!ti) val[ti = v++] = t;
    adj[i].push_back(si);
    adj[i].push_back(ti);
  }
  memset(mate, -1, sizeof(mate));
  memset(seen, -1, sizeof(seen));
  
  for (int i = 0; i < n; ++i)
    assert(extend(i, ++cookie));

  int iterations = 0;
  while (true) {
    ++iterations;
    if (DEBUG) {
      ll tot = 0;
      for (int v = 0; v < n; ++v) {
	int other = mate[v] == adj[v][0] ? adj[v][1] : adj[v][0];
	tot += val[other];
      }
      fprintf(stderr, "Make round of improvements.  Current score %lld\n", tot);
      if (n < 100) {
	for (int i = 0; i < n; ++i)
	  printf("  %d -> %d\n",
		 i, val[mate[i]]);
      }
    }
    bool improved = false;
    for (int i = 0; i < n; ++i) {
      if (mate[i] == adj[i][1] && val[adj[i][1]] > val[adj[i][0]]) {
	//	printf("cand %d -> %d instead of %d\n", i, val[adj[i][1]], val[adj[i][0]]);
	unmatch(i);
	if (mate[adj[i][0]] == -1 ||
	    improve(mate[adj[i][0]], ++cookie, val[adj[i][1]] - val[adj[i][0]])) {
	  //printf("improve succeeded\n") ;
	  improved = true;
	  match(i, adj[i][0]);
	} else {
	  match(i, adj[i][1]);
	}
      }
    }
    if (!improved) break;
  }
  fprintf(stderr, "%d iterations\n", iterations);
  
  ll tot = 0;
  for (int v = 0; v < n; ++v) {
    int other = mate[v] == adj[v][0] ? adj[v][1] : adj[v][0];
    tot += val[other];
  }
  printf("%lld\n", tot);
}
