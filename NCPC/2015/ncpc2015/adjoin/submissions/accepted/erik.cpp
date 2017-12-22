#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#define rep(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int n_v, n_e;
int comp[100000+10];
int path[100000+10];

ostream& operator<<(ostream& os, const vi&v) {
	rep(i,0,v.size())
		os << v[i] << ' ';
	return os;
}

int main() {
	scanf("%d%d", &n_v, &n_e);
	vvi adj(n_v, vi(0));
  vvi succ(n_v, vi(0));
  vi parent(n_v, -1);
  vi depth(n_v, 0); //depth[i] = distance to deepest node in subtree rooted at i
  vi score(n_v, -1), sdore(n_v, 0);
	for(int i = 0; i < n_e; ++i) {
		int a,b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
  rep(i,0,n_v)
		comp[i] = -1;
  int n_t=0;
  vi D;
  rep(i,0,n_v) {
		if(comp[i] == -1) {
			comp[i] = n_t++;	
			queue<int> q;
			q.push(i);
			while(q.size()) {
				int u = q.front(); q.pop();
				int ct = 0;
        rep(j,0,adj[u].size()) {
					int v = adj[u][j];
					if(comp[v] == -1) {
						comp[v] = comp[u];
            parent[v] = u;
            succ[u].push_back(v);
						q.push(v);
					}
				}
			}
      int diam = 0;
      {//do non-recursive DFS from i, the root node
      int p = i, k = 0;
      do {
        //aim
        if(score[p] == -1) {
          score[p] = 0;path[k] = 0;
        } else {
          int tmp = 1 + score[succ[p][path[k]]];
          if(tmp >= sdore[p]) {
            sdore[p] = tmp;
            if(score[p] < sdore[p]) swap(score[p], sdore[p]);
          }
          ++path[k]; 
        }
        //move
        if(path[k] == succ[p].size()) {
          diam = max(diam, score[p] + sdore[p]);
          p = parent[p]; --k;
        } else {
          p = succ[p][path[k]]; ++k;
        }
      } while(k >= 0); } 
      //cout << "found a new tree rooted at " << i << ", with diameter " << diam << endl; 
      D.push_back(diam);
		}
	}
  sort(D.begin(), D.end());
  reverse(D.begin(), D.end());
  assert(D.size() == n_t); 
  int ans = 0;
  if(n_t > 0) ans = max(ans, D[0]);
  if(n_t > 1) ans = max(ans, (D[0]+1)/2 + 1 + (D[1]+1)/2);
  if(n_t > 2) ans = max(ans, (D[1]+1)/2 + 2 + (D[2]+1)/2);
  cout << ans << endl;

	return 0;
}
