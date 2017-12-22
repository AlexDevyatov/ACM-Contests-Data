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

vector<int> ptr;
vector<int> txt;
vector<int> P;
vector<int> A;

inline void fillP(){
	int n = ptr.size();
	P=vector<int>(n+1,0);
	P[0]=0;
	FOR(i,1,n-1){
		int a=P[i-1];
		while (a>0 && ptr[a]!=ptr[i]) a=P[a-1];
		P[i]=a+((ptr[a]==ptr[i])?1:0);
	}
}

inline void fillA(){
	int m = txt.size();
	A=vector<int>(m,0);
	A[0]=((ptr[0]==txt[0])?1:0);
	FOR(i,1,m-1){
		int a=A[i-1];
		while (a>0 && ptr[a]!=txt[i]) a=P[a-1];
		A[i]=a+((ptr[a]==txt[i])?1:0);
	}
}

inline void adjust(vector<int>& r){
	sort(r.begin(),r.end());
	int b=r[0]+360*1000-r[r.size()-1];
	FORD(i,r.size()-1,1) r[i]-=r[i-1];
	r[0]=b;
}

vector<int> c[2];

int main(){
	int n,a;
	scanf("%d",&n);
	REP(i,n){scanf("%d",&a); c[0].PB(a);}
	REP(i,n){scanf("%d",&a); c[1].PB(a);}
	adjust(c[0]); adjust(c[1]);
	
	REP(t,2) REP(i,n) txt.PB(c[0][i]);
	         REP(i,n) ptr.PB(c[1][i]);

	fillP();
	fillA();
	REP(i,A.size()) if (A[i]==n) {printf("possible\n"); return 0;}

	printf("impossible\n");
	return 0;
}

