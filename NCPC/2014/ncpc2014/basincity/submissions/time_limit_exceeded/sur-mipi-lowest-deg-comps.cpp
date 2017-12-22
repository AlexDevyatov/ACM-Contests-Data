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


/* ================ */

int n,k;
int G[MAX][10];
bool M[MAX][MAX];
int deg[MAX];
int color[MAX];
int len,cur;
int fnd;
int st[10000];
int cdeg[MAX];
int lst[MAX];
int lstSize;
int stSize;
int maxFnd;

void giveAnswer(int ans){
	if (ans) printf("possible\n"); else printf("impossible\n");
	exit(0);
}

/* Takes v to the solution and marks neighbors as deleted. 
   Returns the number of performed markings (for reverting changes). */
int doMark(int v){
	//printf("Marking %d\n",v);
	int ret=1;
	color[v]=1;
	st[stSize++]=v;
	REP(i,deg[v]){
		int w=G[v][i];
		if (!(color[w])){
			color[w]=-1; 
			st[stSize++]=w; 
			ret++;
		}
	}
	return ret;
}

/* Reverts num changes */
inline void doUnmark(int num){ REP(i,num) color[st[--stSize]]=0;}

void backtrack(){
	//printf("Tracking fnd=%d\n",fnd);
	if (fnd>=k) giveAnswer(1);

	lstSize=0;
	int nPush=0;

	/* Find the currently lowest degree */
	int bestDeg=100;
	REP(t,n) if (!color[t]) {
		lst[lstSize++]=t;
		int dg=0;
		REP(j,deg[t]) if (!color[G[t][j]]) dg++;
		cdeg[t]=dg;
		if (dg<bestDeg) bestDeg=dg;
	}

	/* If there are no vertices left, answer NO. 
           If there are vertices left and we lack one vertex, answer YES */
	if (bestDeg==100) {if (fnd>maxFnd) maxFnd=fnd; return;}
	if (fnd>=k-1) giveAnswer(1);

	/* If there are degree-0 or degree-1 vertices, take them greedily */
	if (bestDeg<2){
		int nFnd=0;
		REP(t,lstSize){			
			int u=lst[t];
			if ((color[u]) || (cdeg[u]>1)) continue;
			nPush+=doMark(u);
			nFnd++;
		}
//		printf("%d\n",nFnd);
		fnd+=nFnd;
		backtrack();
		fnd-=nFnd;
		doUnmark(nPush);
		return;
	}
	
	/* Find the smallest degree vertex to branch on */
	int u=-1;
	REP(t,lstSize) if (cdeg[lst[t]]==bestDeg){u=lst[t]; break;}
	
	/* Branch where u is taken */
	nPush = doMark(u);
	fnd++;
	backtrack();
	fnd--;
	doUnmark(nPush);

	/* Branches where neighbors of u are taken */
	REP(j,deg[u]) {
		int w1 = G[u][j];
		if (color[w1]) continue;
		nPush=doMark(w1);
		fnd++;
		backtrack();
		fnd--;
		doUnmark(nPush);
	}
}

/* ================ */

int on;
bool oM[MAX][MAX];
int component[MAX];
int num_comp;

void dfs(int u, int c){
	component[u]=c;
	REP(i,on) if (oM[u][i] && (component[i]==0)) dfs(i,c);
}

inline void partitionIntoComponents(){
	num_comp=0;
	REP(i,on) if (component[i]==0) dfs(i,++num_comp);
}

int processComponent(int c){
	vector<int> members;
	REP(i,on) if (component[i]==c) members.PB(i);

	n=members.size();
	REP(i,n) color[i]=deg[i]=0;
	REP(i,n) REP(j,n) M[i][j]=false;

	REP(i,n) REP(j,i){
		if (oM[members[i]][members[j]]){
			M[i][j]=M[j][i]=true;
			G[i][deg[i]++]=j;
			G[j][deg[j]++]=i;
		}
	}

	stSize=0;
	maxFnd=0;
	backtrack();

	return maxFnd;	
}

int main(){
	scanf("%d\n%d\n",&k,&on);

	if (on>=k*5) giveAnswer(1);

	REP(i,on) REP(j,on) oM[i][j]=false;

	REP(i,on){
		int d;
		scanf("%d",&d);
		component[i]=0;
		REP(j,d){
			int v;
			scanf("%d",&v); v--;
			oM[i][v]=oM[v][i]=true;
		}
	}
	
	int mx=0;
	partitionIntoComponents();
	REP(t,num_comp){
		int nextMx=processComponent(t+1);
		if (nextMx>=k) giveAnswer(1);
		k-=nextMx;
	}

	giveAnswer(0);
	return 0;
}

