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

#define MAXN 500
#define MAXM 2000

int maxcrd;

bool M[MAXN][MAXN];

vector<PII> crd;
vector<PII> edges;
vector<PII> queries;

int n,m;

inline void put_edge(int i,int j){
	M[i][j]=M[j][i]=true;
}

const int wchuj = 10000000;

inline void prepare_edges(){
	REP(j,n) REP(i,j){
		if (M[i][j]){
			if (rand()%2==0) edges.PB(MP(i,j)); else edges.PB(MP(j,i));
		}
	}
	m=edges.size();
	REP(t,wchuj){
		int i=rand()%m;
		int j=rand()%m;
		swap(edges[i],edges[j]);
	}	
}

inline void shuffle_nodes(){
	vector<int> prm;
	REP(i,n) prm.PB(i);
	REP(t,wchuj){
		int i=rand()%n;
		int j=rand()%n;
		swap(prm[i],prm[j]);
	}

	vector<PII> crdp = vector<PII>(n,MP(0,0));
	REP(i,n) crdp[prm[i]]=crd[i];
	crd=crdp;

	REP(i,m) {
		edges[i].F=prm[edges[i].F];
		edges[i].S=prm[edges[i].S];
	}

	REP(i,queries.size()){
		queries[i].F=prm[queries[i].F];
		queries[i].S=prm[queries[i].S];
	}
}

inline void shuffle_queries(){
	int s=queries.size();
	REP(t,wchuj){
		int i=rand()%s;
		int j=rand()%s;
		swap(queries[i],queries[j]);
	}
}

inline void printOutput(){
	printf("%d\n",n);
	REP(i,n) printf("%d %d\n",crd[i].F,crd[i].S);
	printf("%d\n",m);
	REP(i,m) printf("%d %d\n",edges[i].F+1,edges[i].S+1);
	printf("%d\n",queries.size());
	REP(i,queries.size()) printf("%d %d\n",queries[i].F+1,queries[i].S+1);
}

set<PII> used;

PII get_unused(){
	int a=rand()%(2*maxcrd+1) - maxcrd;
	int b=rand()%(2*maxcrd+1) - maxcrd;
	PII p=MP(a,b);
	if (used.count(p)>0) return get_unused();
	used.insert(p);
	return p;
}

PII get_unused(PII center, int rad){
	int a=center.F+rand()%(2*rad+1) - rad;
	int b=center.S+rand()%(2*rad+1) - rad;
	PII p=MP(a,b);
	if (used.count(p)>0) return get_unused(center,rad);
	used.insert(p);
	return p;
}

void runGen3(){
	n=44;

	REP(i,n) REP(j,n) M[i][j]=false;
	FOR(t,-10,10){
		int y=((t%2)==0)?100:90;
		crd.PB(MP(t,y));
		crd.PB(MP(t,-y));
		if (t>-10){
			put_edge(2*(t+10),2*(t+9));
			put_edge(2*(t+10)+1,2*(t+9)+1);
		}
	}
	crd.PB(MP(-100,0));
	crd.PB(MP(100,0));

	put_edge(0,40);
	put_edge(1,41);

	put_edge(42,0);
	put_edge(42,1);

	put_edge(43,40);
	put_edge(43,41);

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();
}

void runGen4(){
	maxcrd=200;

	n=60;
	REP(i,n) crd.PB(get_unused());
	REP(i,n) REP(j,n) M[i][j]=false;	
	REP(j,n) REP(i,j){
		if (rand()%3==0) put_edge(i,j);
	}

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();
}

void runGen5(){
	maxcrd=1000;

	n=500;
	REP(i,n) crd.PB(get_unused());
	REP(i,n) REP(j,n) M[i][j]=false;	
	REP(i,n) put_edge(i,(i+1)%n);

	vector<int> perm; REP(i,n/2) perm.PB(i);
	REP(t,wchuj){
		int i=rand()%(n/2);
		int j=rand()%(n/2);
		swap(perm[i],perm[j]);
	}
	REP(i,n/2){
		put_edge(i,perm[i]+n/2);
	}

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();
}

void runGen6(){
	n=500;
	PII cu=MP(50,0);
	PII dir=MP(1,2);
	REP(i,400){
		crd.PB(cu);
		cu.F+=dir.F; cu.S+=dir.S;

		if (i==49) dir=MP(-2,-1);
		if (i==99) dir=MP(-2,1);
		if (i==149) dir=MP(1,-2);
		if (i==199) dir=MP(-1,-2);
		if (i==249) dir=MP(2,1);
		if (i==299) dir=MP(2,-1);
		if (i==349) dir=MP(-1,2);
	}
	
	REP(i,n) REP(j,n) M[i][j]=false;	
	REP(i,400) put_edge(i,(i+1)%400);

	REP(i,50){
		int k1=1+rand()%5;
		int k2=1+rand()%5;
		crd.PB(MP(50+(i+1)+k1,2*(i+1)));
		crd.PB(MP(50+(i+1)+k1+k2,2*(i+1)));
		put_edge(i,400+2*i);
		put_edge(400+2*i+1,400+2*i);
	}

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();
}

void runGen7(){
	n=400;
	maxcrd=300;

	crd=vector<PII>(n,MP(0,0));
	REP(i,20) crd[i*20]=get_unused();
	REP(i,19) put_edge(i*20,(i+1)*20);

	REP(i,20){
		int c=20*i;
		REP(t,19) crd[c+1+t]=get_unused(crd[c],20);
		REP(t,20) put_edge(c+t,c+(t+1)%20);
		put_edge(c+3,c+17);
		put_edge(c+5,c+8);
		put_edge(c+10,c+12);
		put_edge(c+1,c+10);
		put_edge(c+5,c+15);
	}

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();
}

bool is_inside(PII cnd){
	return ((cnd.F<100) && (cnd.F + cnd.S*2 > -100) && (cnd.F + cnd.S*(-2) > -100));
}

void runGen8(){
	n=500;
	maxcrd=100;
	PII cu=MP(100,-100);
	PII dir=MP(0,2);
	REP(i,300){
		crd.PB(cu);
		cu.F+=dir.F; cu.S+=dir.S;

		if (i==99) dir=MP(-2,-1);
		if (i==199) dir=MP(2,-1);
	}
	REP(i,300) put_edge(i,(i+1)%300);
	REP(i,200){
		PII cnd=get_unused();
		while (!is_inside(cnd)) cnd=get_unused();
		int c=crd.size(); crd.PB(cnd);
		int r=rand()%300;
		put_edge(c,r);
		put_edge(c,(r+1)%300);
	}

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();
}

void runGen9(){
	n=500;
	maxcrd=10000;

	REP(i,n) crd.PB(get_unused());

	REP(i,n) REP(j,n) M[i][j]=false;	
	REP(i,n) put_edge(i,(i+1)%n);

	REP(i,3*n){
		int a,b;
		for(;;){
			a=rand()%n;
			b=rand()%n;
			if ((a!=b) && (!M[a][b])) break;
		}
		put_edge(a,b);
	}

	REP(i,n) REP(j,i) queries.PB(MP(i,j));

	prepare_edges();
	shuffle_nodes();
	shuffle_queries();
	printOutput();

}

int main(int argc, char** argv){
	int cs = atoi(argv[1]);
	srand(2387232*cs+4933245);
	switch (cs){
		case 3: runGen3(); return 0;
		case 4: runGen4(); return 0;
		case 5: runGen5(); return 0;
		case 6: runGen6(); return 0;
		case 7: runGen7(); return 0;
		case 8: runGen8(); return 0;
		case 9: runGen9(); return 0;
/*		case 10: runGen10(); return 0;
		case 11: runGen11(); return 0;
		case 12: runGen12(); return 0;*/
	}
	return 0;
}

