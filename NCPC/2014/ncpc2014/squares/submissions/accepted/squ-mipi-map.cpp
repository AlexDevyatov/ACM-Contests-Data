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

LL gcd(LL a,LL b){
	if (b==0) return a; else return gcd(b,a%b);
}

struct Functional {
	LL x;
	LL y;
	LL v;

	Functional(LL x1, LL y1, LL x2, LL y2){
		y=x1-x2; x=y2-y1;

		if ((x<0)||(x==0 && y<0)){
			x=-x;
			y=-y;
		}
		LL d = gcd(llabs(x),llabs(y));
		x/=d;
		y/=d;
	
		v=x*x1+y*y1;
	}

	Functional(const Functional& f){x=f.x; y=f.y; v=f.v;}

	int quadrant() const {
		if (y>0) return 1; else return 0;
	}

	bool operator<(const Functional& f) const {
		LL k = x*f.y-y*f.x;
		if (k==0) return (v<f.v); else return (k>0);
	}

	bool operator==(const Functional& f) const {
		return (x==f.x && y==f.y && v==f.v);
	}

	bool sameVec(const Functional& f) const {
		return (x==f.x && y==f.y);
	}

	LL dotProd(const Functional& f) const {
		return (x*f.x+y*f.y);
	}

	void printSelf() const {
		printf("%lld %lld %lld\n",x,y,v);
	}
};

vector<Functional> q0;
vector<Functional> q1;

int n;

LL countSquares(const vector<LL>& r1,const vector<LL>& r2){
	LL ret=0;	
	map<LL,int> p;
	REP(j,r1.size()) REP(i,j){
		LL d = r1[j]-r1[i];
		if (p.count(d)>0) p[d]++; else p[d]=1;
	}
	REP(j,r2.size()) REP(i,j) {
		LL d = r2[j]-r2[i];
		if (p.count(d)>0) ret+=p[d];
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	REP(i,n){
		LL x1,y1,x2,y2;
		scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		Functional r = Functional(x1,y1,x2,y2);
		if (r.quadrant()) {q1.PB(r);} else {q0.PB(r);}
	}
	sort(q0.begin(),q0.end());
	sort(q1.begin(),q1.end());

	LL ret=0;

	int c=0,d=0;
	vector<LL> r1,r2;
	while(c<q0.size()){
		int cc=c+1;
		r1.clear(); r1.PB(q0[c].v);
		for(;cc<q0.size();cc++){
			if (!q0[c].sameVec(q0[cc])) break; else r1.PB(q0[cc].v);
		}
		int dd=d; r2.clear();
		for(;dd<q1.size();dd++){
			LL u = q0[c].dotProd(q1[dd]);
			if (u==0LL) r2.PB(q1[dd].v);
			if (u<0) break;
		}
		ret+=countSquares(r1,r2);
		c=cc; d=dd;
	}
	printf("%lld\n",ret);
	return 0;
}

