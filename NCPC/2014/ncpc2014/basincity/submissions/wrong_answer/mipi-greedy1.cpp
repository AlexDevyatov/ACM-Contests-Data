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

#define MAX 100

int n,k;
int G[MAX][10];
int deg[MAX];
int rdeg[MAX];
bool del[MAX];
int d;

inline void deleteVertex(int v){
	if (!del[v]){
		REP(t,deg[v]) rdeg[G[v][t]]--;
		del[v]=true;
		d++;
	}
}

inline void doScan(){
	int bst=1000;
	REP(v,n) if (!del[v]){
		if (rdeg[v]<bst) bst=rdeg[v];

		if (rdeg[v]==0) {
			del[v]=true; d++;
			k--;
		}
		if (rdeg[v]==1) {
			del[v]=true; d++;
			REP(t,deg[v])
				deleteVertex(G[v][t]);
			k--;		
		}
	}
	if (bst<2) return;
	vector<int> cand;
	REP(v,n) if (!del[v] && rdeg[v]==bst) cand.PB(v);
	int l = rand()%(cand.size()); int vv=cand[l];
	del[vv]=true; d++;
	REP(t,deg[vv])
		deleteVertex(G[vv][t]);
	k--;
}

void giveAnswer(int ans){
	if (ans) printf("possible\n"); else printf("impossible\n");
	exit(0);
}

const int wchuj=200000;

int main(){
	srand(time(0));
	int kk;
	scanf("%d\n%d\n",&kk,&n);

	if (n>=kk*5) giveAnswer(1);

	REP(i,n){
		int dg;
		scanf("%d",&dg); deg[i]=dg;
		REP(j,dg){
			int v;
			scanf("%d",&v);
			G[i][j]=v-1;
		}
	}

	REP(t,wchuj){
		d=0;
		k=kk;
		REP(i,n) {rdeg[i]=deg[i]; del[i]=false;}
		while(d<n){
			doScan();
			if (k<=0) giveAnswer(1);
		}
	}

	giveAnswer(0);
	return 0;
}

