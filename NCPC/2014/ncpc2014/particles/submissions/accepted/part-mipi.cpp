/* Solution of problem Particle Swapping	*
 * Time complexity: O(n^2 log n)		*
 * Author: Michal Pilipczuk			*/

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
vector<vector<PII> > members;
vector<PII> sorted;
vector<PII> queries;
vector<PII> crd;

int curmin;

vector<PII> get_neighbors(PII s){
	int u=s.F, v=s.S;
	vector<PII> ret;
	REP(t,gG[u].size()) ret.PB(MP(gG[u][t],v));
	REP(t,gG[v].size()) ret.PB(MP(u,gG[v][t]));
	return ret;
}

bool cmp(PII a,PII b){
	return (safeness[a.F][a.S]>safeness[b.F][b.S]);
}

inline int dist(int a, int b){
	return (crd[a].F-crd[b].F)*(crd[a].F-crd[b].F)+(crd[a].S-crd[b].S)*(crd[a].S-crd[b].S);
}

inline void add_edge_G(int u, int v){
	gG[u].PB(v);
	gG[v].PB(u);
}

inline void read_input(){
	scanf("%d",&n);
	crd.clear();
	REP(i,n){
		int x,y;
		scanf("%d%d",&x,&y);
		crd.PB(MP(x,y));
	}

	gG.resize(n);
	members.resize(n*n);

	scanf("%d",&m);
	REP(i,m){
		int a,b;
		scanf("%d%d",&a,&b); a--; b--;
		add_edge_G(a,b);
	}

	scanf("%d",&l);
	queries.clear();
	REP(i,l){
		int a,b;
		scanf("%d%d",&a,&b); a--; b--;
		queries.PB(MP(a,b));
	}

	sorted.clear();
	REP(i,n) REP(j,n){
		safeness[i][j]=dist(i,j);
		sorted.PB(MP(i,j));
		processed[i][j]=false;
		component[i][j]=i*n+j;
		members[i*n+j].PB(MP(i,j));
		result[i][j]=-1;
	}

	sort(ALL(sorted),cmp);
}

inline void join(PII u, PII v){
	int c1 = component[u.F][u.S];
	int c2 = component[v.F][v.S];
	if (c1==c2) return;
	if (members[c1].size()>members[c2].size()) swap(c1,c2);
	REP(j,members[c1].size()){
		PII m = members[c1][j];
		component[m.F][m.S]=c2;
		members[c2].PB(m);
		if (result[m.F][m.S]<0 && component[m.S][m.F]==c2)
			result[m.F][m.S] = result[m.S][m.F] = curmin;
	}
	members[c1].clear();
}

inline void compute_solution(){
	REP(t,sorted.size()){
		PII u = sorted[t];
		curmin = safeness[u.F][u.S];
		vector<PII> nei = get_neighbors(u);
		REP(i,nei.size()){
			PII v = nei[i];
			if (processed[v.F][v.S]) join(u,v);
		}
		processed[u.F][u.S]=true;
	}
}

inline void write_output(){
	REP(i,l) {
		printf("%.10Lf\n",sqrtl(result[queries[i].F][queries[i].S]));
//		int r=(result[queries[i].F][queries[i].S]==safeness[queries[i].F][queries[i].S])?1:0;
//		printf("%.8Lf %d\n",sqrtl(result[queries[i].F][queries[i].S]),r);
	}
}

int main(){
	read_input();
	compute_solution();
	write_output();
	return 0;
}

