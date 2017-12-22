/* Brute force solution of the problem Particle Swapping	*
 * Search on state graph, time complexity O(n^4 log n)		*
 * Author: Michal Pilipczuk					*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;

typedef pair<int,int> PII;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<(n); ++i)
#define FOR(var,pocz,koniec) for (int var=(pocz); var<=(koniec); ++var)
#define FORD(var,pocz,koniec) for (int var=(pocz); var>=(koniec); --var)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define F first
#define S second
#define LD long double

#define MAXN 600

int n,m,l;

int vis[MAXN][MAXN];

vector<vector<int> > gG;
vector<PII> crd;

vector<PII> get_neighbors(PII s){
	int u=s.F, v=s.S;
	vector<PII> ret;
	REP(t,gG[u].size()) ret.PB(MP(gG[u][t],v));
	REP(t,gG[v].size()) ret.PB(MP(u,gG[v][t]));
	return ret;
}

inline int dist(int a, int b){
	return (crd[a].F-crd[b].F)*(crd[a].F-crd[b].F)+(crd[a].S-crd[b].S)*(crd[a].S-crd[b].S);
}

inline void add_edge_G(int u, int v){
	gG[u].PB(v);
	gG[v].PB(u);
}

priority_queue<pair<int,PII> > q;

int query(int a,int b,int i){
	q=priority_queue<pair<int,PII> >();
	int mx=dist(a,b);
	q.push(MP(mx,MP(a,b)));
	vis[a][b]=i;
	for(;;){
		pair<int,PII> nxt = q.top();
		q.pop();
		if (mx>nxt.F) mx=nxt.F;
		if ((nxt.S.F == b) && (nxt.S.S == a)) return mx;
		vector<PII> nei = get_neighbors(nxt.S);
		REP(t,nei.size()){
			PII w = nei[t];
			if (vis[w.F][w.S]==i) continue;
			vis[w.F][w.S]=i;
			q.push(MP(dist(w.F,w.S),w));
		}
	}
	/* this should never happen */
	return -1;
}

int main(){
	scanf("%d",&n);
	crd.clear();
	REP(i,n){
		int x,y;
		scanf("%d%d",&x,&y);
		crd.PB(MP(x,y));
	}

	gG.resize(n);

	scanf("%d",&m);
	REP(i,m){
		int a,b;
		scanf("%d%d",&a,&b); a--; b--;
		add_edge_G(a,b);
	}

	scanf("%d",&l);
	REP(i,l){
		int a,b;
		scanf("%d%d",&a,&b); a--; b--;
		printf("%.8Lf\n",sqrtl(query(a,b,i+1)));
	}

	return 0;
}

