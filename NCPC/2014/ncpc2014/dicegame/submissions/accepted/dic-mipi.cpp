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

vector<int> A[2]; 

int main(){
	REP(t,2) REP(i,4){
		int a;
		scanf("%d",&a);
		A[t].PB(a);
	}
	int a1=0,a2=0;
	FOR(i1,A[0][0],A[0][1]) FOR(i2,A[0][2],A[0][3]) FOR(i3,A[1][0],A[1][1]) FOR(i4,A[1][2],A[1][3]){
		int k1 = i1+i2;
		int k2 = i3+i4;
		if (k1>k2) a1++;
		if (k1<k2) a2++;
	}
	if (a1>a2) printf("Gunnar\n");
	if (a1<a2) printf("Emma\n");
	if (a1==a2) printf("Tie\n");
	return 0;
}

