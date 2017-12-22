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

#define MAX 300

int main(){
	int n,C,a,b,c,r=0;
	scanf("%d%d",&C,&n);
	REP(i,n){
		scanf("%d%d%d",&a,&b,&c);
		r-=a; if (r<0) goto hell;
		r+=b; if (r>C) goto hell;
		if ((c>0)&&(r<C)) goto hell;
	}
	if (r!=0) goto hell;

	printf("possible\n");
	return 0;
hell:
	printf("impossible\n");
	return 0;
}

