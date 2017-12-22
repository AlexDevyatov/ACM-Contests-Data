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

	Line(){p1=MP(0,0); p2=MP(0,0);}

	Line(PLL q1,PLL q2){
		p1=q1; p2=q2;
	}

	Line(const Line& l){
		p1=l.p1; p2=l.p2;
	}

	Line operator=(const Line& l){
		p1=l.p1; p2=l.p2;
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

struct LinePair{
	Line l1;
	Line l2;
	PLL dst;

	LinePair(const Line& ll1,const Line& ll2){
		l1=ll1; l2=ll2; dst=l1.dist(l2.p1);
	}

	bool operator<(const LinePair& q) const{
		return (dst<q.dst);
	}

};

vector<Line> input;
vector<LinePair> cand;

int main(){
	int n;
	scanf("%d",&n);
	REP(i,n){
		LL x1,y1,x2,y2;
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		input.PB(Line(MP(x1,y1), MP(x2,y2)));	
	}

	LL ret =0;

	REP(j,n) REP(i,j) if (input[i].parallel(input[j])) cand.PB(LinePair(input[i],input[j]));		

	sort(cand.begin(), cand.end());

	int s=cand.size(),c=0;
	while(c<s){
		int cc=c+1;
		for(;cc<s;cc++) if (cand[c].dst!=cand[cc].dst) break;
		FOR(i,c+1,cc-1) FOR(j,c,i-1) if (cand[i].l1.perpendicular(cand[j].l1)) ret++;
		c=cc;
	}

	printf("%lld\n",ret);
	return 0;
}

