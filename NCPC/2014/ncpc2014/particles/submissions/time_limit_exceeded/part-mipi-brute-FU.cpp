/* Brute force solution of the problem Particle Swapping	*
 * Sorted FU on state graph, time complexity O(n^4 log n)	*
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

int result[MAXN][MAXN];
int component[MAXN][MAXN];
int safeness[MAXN][MAXN];
bool processed[MAXN][MAXN];

vector<vector<int> > gG;
vector<PII> sorted;
vector<PII> crd;

bool cmp(PII a,PII b){
	return (safeness[a.F][a.S]>safeness[b.F][b.S]);
}

PII FU[MAXN][MAXN];

PII FUFind(PII r){
	if (FU[r.F][r.S].F<0) return r; else return (FU[r.F][r.S]=FUFind(FU[r.F][r.S]));
}

inline void FUJoin(PII r1,PII r2){
	r1=FUFind(r1); r2=FUFind(r2);
	if (r1==r2) return;
	if (FU[r1.F][r1.S].F>FU[r2.F][r2.S].F) swap(r1,r2);
	FU[r1.F][r1.S].F+=FU[r2.F][r2.S].F;
	FU[r2.F][r2.S]=r1;
}

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

int query(int a,int b){
	REP(i,n) REP(j,n) {FU[i][j]=MP(-1,0); processed[i][j]=false;}

	int curmin = 0;

	REP(t,sorted.size()){
		PII u = sorted[t];
		vector<PII> nei = get_neighbors(u);
		REP(i,nei.size()){
			PII v = nei[i];
			if (processed[v.F][v.S]) FUJoin(u,v);
		}
		processed[u.F][u.S]=true;
		if (processed[a][b] && processed[b][a] && FUFind(MP(a,b))==FUFind(MP(b,a))) return safeness[u.F][u.S];
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

	sorted.clear();
	REP(i,n) REP(j,n){
		safeness[i][j]=dist(i,j);
		sorted.PB(MP(i,j));
	}

	sort(ALL(sorted),cmp);

	scanf("%d",&l);
	REP(i,l){
		int a,b;
		scanf("%d%d",&a,&b); a--; b--;
		printf("%.8Lf\n",sqrtl(query(a,b)));
	}

	return 0;
}

