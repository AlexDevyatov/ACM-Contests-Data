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

vector<PII> crd;

int main(){
	scanf("%d",&n);
	crd.clear();
	REP(i,n){
		int x,y;
		scanf("%d%d",&x,&y);
		crd.PB(MP(x,y));
	}

	scanf("%d",&m);
	REP(i,m){
		int a,b;
		scanf("%d%d",&a,&b);
	}

	scanf("%d",&l);
	REP(i,l){
		int a,b;
		scanf("%d%d",&a,&b); a--; b--;
		int m = (crd[a].F-crd[b].F)*(crd[a].F-crd[b].F)+(crd[a].S-crd[b].S)*(crd[a].S-crd[b].S);
		printf("%.10Lf\n",sqrtl((double)m));
	}
	return 0;
}

