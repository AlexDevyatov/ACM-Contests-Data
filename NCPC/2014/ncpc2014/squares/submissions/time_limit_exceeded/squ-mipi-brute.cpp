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
#define LL long long

typedef pair<LL,LL> PLL;

#define MAX 300

LL gcd(LL a, LL b){
	if (b==0) return a; else return gcd(b,a%b);
}

struct Line{
	PLL p1;
	PLL p2;

	Line(PLL q1,PLL q2){
		p1=q1; p2=q2;
	}

	bool parallel(const Line& l) const {
		return (p1.F-p2.F)*(l.p1.S-l.p2.S)==(p1.S-p2.S)*(l.p1.F-l.p2.F);
	}

	bool perpendicular(const Line& l) const {
		return (p1.F-p2.F)*(l.p1.F-l.p2.F)+(p1.S-p2.S)*(l.p1.S-l.p2.S)==0;
	}

	PLL dist(PLL p) const {
		LL num = (p.F-p1.F)*(p2.S-p1.S) - (p.S-p1.S)*(p2.F-p1.F);
		num*=num;
		LL denom = (p2.F-p1.F)*(p2.F-p1.F) + (p2.S-p1.S)*(p2.S-p1.S);
		LL d = gcd(num,denom);
		num/=d; denom/=d;
		return MP(num, denom);
	}
};

vector<Line> input;

int main(){
	int n;
	scanf("%d",&n);
	REP(i,n){
		LL x1,y1,x2,y2;
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		input.PB(Line(MP(x1,y1), MP(x2,y2)));	
	}

	LL ret =0;

	REP(j1,n) REP(i1,j1) {
		if (!input[i1].parallel(input[j1])) continue;
		PLL t1=input[i1].dist(input[j1].p1);
		REP(j2,j1) {
			if (!input[i1].perpendicular(input[j2])) continue;
			REP(i2,j2){
				if (!input[i2].parallel(input[j2])) continue;
				PLL t2 = input[i2].dist(input[j2].p1);
				if (t1.F==t2.F && t1.S==t2.S) ret++;
			}
		}
	}

	printf("%lld\n",ret);
	return 0;
}

