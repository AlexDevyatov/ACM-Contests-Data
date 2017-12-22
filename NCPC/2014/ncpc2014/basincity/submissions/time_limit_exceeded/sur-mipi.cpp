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
int color[MAX];
int len,cur;
int fnd;
stack<int> st;

int doMark(int v){
	int ret=1;
	color[v]=1;
	st.push(v);
//	printf("Marking %d, fnd=%d\n",v,fnd);
	REP(i,deg[v]){
		int w=G[v][i];
		if (!(color[w])){
//			printf("Excluding %d\n",w); 
			color[w]=-1; 
			st.push(w); 
			ret++;
		}
	}
	return ret;
}

inline void doPop(){
	int t = st.top();
//	printf("Unmarking %d\n",t);
	st.pop();
	color[t]=0;
}

inline void doUnmark(int num){ REP(i,num) doPop();}

void giveAnswer(int ans){
	if (ans) printf("possible\n"); else printf("impossible\n");
	exit(0);
}

void backtrack(int dp){
	if (fnd==k) giveAnswer(1);
	if (dp==n) return;
	if (color[dp]) {backtrack(dp+1); return;}

	int toPop = doMark(dp);
	fnd++;
	backtrack(dp+1);
	doUnmark(toPop);
	fnd--;
	
	REP(t,deg[dp]){
		int w = G[dp][t];
		if (color[w]) continue;
		int toPop = doMark(w);
		fnd++;
		backtrack(dp+1);
		doUnmark(toPop);
		fnd--;
	}
}

int main(){
	scanf("%d\n%d\n",&k,&n);

	if (n>=k*5) giveAnswer(1);

	REP(i,n){
		int d;
		scanf("%d",&d); deg[i]=d;
		color[i]=0;
		REP(j,d){
			int v;
			scanf("%d",&v);
			G[i][j]=v-1;
		}
	}

	fnd=0;
	backtrack(0);
//	printf("HERE!\n");
	giveAnswer(0);
	return 0;
}

