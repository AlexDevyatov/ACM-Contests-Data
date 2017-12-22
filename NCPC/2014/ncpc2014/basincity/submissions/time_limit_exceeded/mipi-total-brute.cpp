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

int n,k,l;
int G[MAX][10];
int deg[MAX];
bool mrk[MAX];

inline void giveAnswer(int ans){
	if (ans) printf("possible\n"); else printf("impossible\n");
	exit(0);
}

inline void verifyStuff(){
	REP(v,n) if (mrk[v]){
		REP(t,deg[v]) if (mrk[G[v][t]]) return;
	}
	giveAnswer(1);
}

void backtrack(int d){
	if (l==k){
		verifyStuff();
		return;
	}
	if (n-d<k-l) return;
	backtrack(d+1);
	mrk[d]=true; l++;
	backtrack(d+1);
	mrk[d]=false; l--;
}

int main(){
	scanf("%d\n%d\n",&k,&n);

	if (n>=k*5) giveAnswer(1);

	REP(i,n){
		int d;
		scanf("%d",&d); deg[i]=d;
		REP(j,d){
			int v;
			scanf("%d",&v);
			G[i][j]=v-1;
		}
	}

	backtrack(0);
	giveAnswer(0);
	return 0;
}

