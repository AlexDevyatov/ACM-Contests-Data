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

LL MaxCrd=10000;

LL gcd(LL a,LL b){
	if (b==0) return a; else return gcd(b,a%b);
}

struct Functional {
	LL x;
	LL y;
	LL v;

	Functional(LL xx, LL yy, LL vv){
		x=xx; y=yy; v=vv;
		if ((x<0)||(x==0 && y<0)){
			x*=(LL)(-1);
			y*=(LL)(-1);
		}
		LL d = gcd(llabs(x),llabs(y));
		x/=d;
		y/=d;
		v/=d;
	}

	Functional(LL x1, LL y1, LL x2, LL y2){
		y=x1-x2; x=y2-y1;

		if ((x<0)||(x==0 && y<0)){
			x*=(LL)(-1);
			y*=(LL)(-1);
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

	pair<PLL, PLL > getTwoPoints(){
		vector<PLL> as;
		if (y!=0){
			FOR(a,-MaxCrd,MaxCrd){
				LL right = v-a*x;
				if (right%y==0 && (right/y<=MaxCrd) && (-MaxCrd<=right/y)) as.PB(MP(a,right/y));
			}
		} else {
			FOR(b,-MaxCrd,MaxCrd){
				LL right = v-b*y;
				if (right%x==0 && (right/x<=MaxCrd) && (-MaxCrd<=right/x)) as.PB(MP(right/x,b));
			}
		}
		int s = as.size();
		int alpha = rand()%s,beta = rand()%s;
		while (alpha==beta) beta = rand()%s;
		return MP(as[alpha],as[beta]);		
	}
};

set<PLL> used;

PLL getUnused(LL c){
	for(;;){
		LL x = rand()%c;
		LL y = rand()%c;
		if (x==0 && y==0) continue;
		LL d = gcd(x,y);
		PLL r = MP(x/d,y/d);
		if (used.count(r)==0){
			used.insert(r);
			return r;
		} 
	}
}

vector<pair<PLL,PLL > > output;

void populateNext(int p1,int p2,LL c,LL step){
	PLL dir = getUnused(c);
	
	LL x1,y1,v;

	x1=(rand()%MaxCrd) - MaxCrd/2;
	y1=(rand()%MaxCrd) - MaxCrd/2;
	v=dir.F*x1+dir.S*y1;
	
	REP(i,p1){
		output.PB(Functional(dir.F,dir.S,v).getTwoPoints());
		v+=(1+rand()%step);
	}

	x1=(rand()%MaxCrd) - MaxCrd/2;
	y1=(rand()%MaxCrd) - MaxCrd/2;
	v=dir.F*x1+dir.S*y1;
	
	REP(i,p2){
		output.PB(Functional(-dir.S,dir.F,v).getTwoPoints());
		v+=(1+rand()%step);
	}
}

const int wchuj = 10000000;

inline void shuffle(){
	int s=output.size();
	REP(t,wchuj){
		int i=rand()%s;
		int j=rand()%s;
		swap(output[i],output[j]);
	}
}

inline void printOutput(){
	printf("%d\n",output.size());
	REP(t,output.size())
		printf("%lld %lld %lld %lld\n",output[t].F.F,output[t].F.S,output[t].S.F,output[t].S.S);
}

void runGen1(){
	MaxCrd=100;
	REP(i,10){
		populateNext(5,5,10,2);
	}
	shuffle();
	printOutput();
}

void runGen2(){
	MaxCrd=1000;
	REP(i,20){
		populateNext(3,2,100,4);
	}
	REP(i,4){
		populateNext(4,6,100,1);
	}
	shuffle();
	printOutput();
}

void runGen3(){
	MaxCrd=1000;
	REP(i,20){
		populateNext(3,1,100,2);
		populateNext(1,4,100,3);
	}
	REP(i,4){
		populateNext(1,0,100,1);
		populateNext(0,1,100,1);
	}
	shuffle();
	printOutput();
}

void runGen4(){
	MaxCrd=5000;
	REP(i,30){
		populateNext(5,5,400,1);
	}
	populateNext(30,33,10,10);
	REP(i,8){
		populateNext(1,0,400,1);
		populateNext(0,1,400,1);
	}
	shuffle();
	printOutput();

}

void runGen5(){
	MaxCrd=5000;
	REP(i,4){
		populateNext(30,30,400,1+rand()%4);
	}
	REP(i,40){
		populateNext(1,4,400,1);
		populateNext(4,1,400,1);
		populateNext(1,1,400,2);
	}
	shuffle();
	printOutput();
}

void runGen6(){
	MaxCrd=10000;
	REP(i,270){
		populateNext(2,3,1000,1+rand()%4);
	}
	shuffle();
	printOutput();
}

void runGen7(){
	MaxCrd=10000;
	REP(i,5){
		populateNext(41,59,700,1);
	}
	REP(i,90){
		populateNext(3,3,700,2);
	}
	REP(i,60){
		populateNext(0,1,1000,1+rand()%4);
		populateNext(1,0,1000,1+rand()%4);
	}
	shuffle();
	printOutput();

}

void runGen8(){
	MaxCrd=10000;
	REP(i,7){
		populateNext(50,50,30,3);
	}
	REP(i,90){
		populateNext(3,3,700,2);
	}
	REP(i,2){
		populateNext(2,3,1000,2);
		populateNext(4,1,1000,2);
	}
	shuffle();
	printOutput();
}

void runGen9(){
	MaxCrd=10000;		
	REP(i,8){
		populateNext(125,125,30,2);
	}
	shuffle();
	printOutput();
}

void runGen10(){
	MaxCrd=10000;

	populateNext(640,653,3,1);
	REP(i,4){
		populateNext(5,5,700,2);
	}
	shuffle();
	printOutput();
}

void runGen11(){
	MaxCrd=10000;
	populateNext(1000,1000,3,1);
	shuffle();
	printOutput();
}

void runGen12(){
	MaxCrd=10000;
	populateNext(1998,2,3,1);
	shuffle();
	printOutput();
}

int main(int argc, char** argv){
	int cs = atoi(argv[1]);
	srand(238746*cs+493889);
	switch (cs){
		case 1: runGen1(); return 0;
		case 2: runGen2(); return 0;
		case 3: runGen3(); return 0;
		case 4: runGen4(); return 0;
		case 5: runGen5(); return 0;
		case 6: runGen6(); return 0;
		case 7: runGen7(); return 0;
		case 8: runGen8(); return 0;
		case 9: runGen9(); return 0;
		case 10: runGen10(); return 0;
		case 11: runGen11(); return 0;
		case 12: runGen12(); return 0;
	}
	return 0;
}

