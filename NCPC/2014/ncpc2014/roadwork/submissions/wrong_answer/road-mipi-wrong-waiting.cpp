/* Wrong transitions in DP: if the car arrived within (when it can go, when it can go +3s), 
   then it is given go immediately. */

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

#define MAX 260

#define INF 1000*1000*1000

#define WEST 0
#define EAST 1

int n;

int cnt[2];

int time_to_pass;
int time_to_wait = 3;

int arrival[2][MAX];
int irrTime[2][MAX];

int T[MAX][MAX][MAX][2];

/* T[s] is the minimum time when 
   - (s.west) cars have been given green light
   - (s.east) cars have been given green light
   - the last car given green light is denoted by (s.state)
   - at most (s.irritated) drivers have been made irritated */

struct State{
	int status; /* 0 - occupied from West, 1 - occupied from East */
	int west;
	int east;
	int irritated;

	State(int s,int w, int e, int i){
		status = s;
		west = w;
		east = e;
		irritated = i;
	}

	void printSelf(const char* msg,int r) const{
//		printf("State (%d,%d,%d,%d), message: %s %d\n",status,west,east,irritated,msg,r);
	}

	void computeValue() const {
		int cnd;
		int bst=INF;

		if (status==WEST){
			if (west==0) return;
			
			/* === Case 1: the previous car was from the west === */
			
			/* Case 1.a: the current car could have got irritated */
			if (irritated>0){
				cnd = T[west-1][east][irritated-1][WEST]+time_to_wait;
				if (arrival[WEST][west-1]>T[west-1][east][irritated-1][WEST]) cnd = arrival[WEST][west-1];
				printSelf("1.a",cnd);
				bst = min(bst,cnd);
			}

			/* Case 1.b: the current car did not get irritated */
			cnd = T[west-1][east][irritated][WEST]+time_to_wait;
			if (arrival[WEST][west-1]>T[west-1][east][irritated][WEST]) cnd = arrival[WEST][west-1];
			if (cnd<=irrTime[WEST][west-1]){
				printSelf("1.b",cnd);
				bst = min(bst,cnd);
			}

			/* === Case 2: the previous car was from the east === */
			
			/* Case 2.a: the current car could have got irritated */
			if (irritated>0){
				cnd = T[west-1][east][irritated-1][EAST]+time_to_pass;
				cnd = max(cnd,arrival[WEST][west-1]);
				printSelf("2.a",cnd);
				bst = min(bst,cnd);
			}

			/* Case 2.b: the current car did not get irritated */
			cnd = T[west-1][east][irritated][EAST]+time_to_pass;
			cnd = max(cnd,arrival[WEST][west-1]);
			if (cnd<=irrTime[WEST][west-1]) {
				printSelf("2.b",cnd);
				bst = min(bst,cnd);
			}
		}

		if (status==EAST){
			if (east==0) return;
			
			/* === Case 1: the previous car was from the east === */
			
			/* Case 1.a: the current car could have got irritated */
			if (irritated>0){
				cnd = T[west][east-1][irritated-1][EAST]+time_to_wait;
				if (arrival[EAST][east-1]>T[west][east-1][irritated-1][EAST]) cnd = arrival[EAST][east-1];
				cnd = max(cnd,arrival[EAST][east-1]);
				printSelf("1.a",cnd);
				bst = min(bst,cnd);
			}

			/* Case 1.b: the current car did not get irritated */
			cnd = T[west][east-1][irritated][EAST]+time_to_wait;
			if (arrival[EAST][east-1]>T[west][east-1][irritated][EAST]) cnd = arrival[EAST][east-1];
			if (cnd<=irrTime[EAST][east-1]) {
				printSelf("1.b",cnd);
				bst = min(bst,cnd);
			}

			/* === Case 2: the previous car was from the west === */
			
			/* Case 2.a: the current car could have got irritated */
			if (irritated>0){
				cnd = T[west][east-1][irritated-1][WEST]+time_to_pass;
				cnd = max(cnd,arrival[EAST][east-1]);
				printSelf("2.a",cnd);
				bst = min(bst,cnd);
			}

			/* Case 2.b: the current car did not get irritated */
			cnd = T[west][east-1][irritated][WEST]+time_to_pass;
			cnd = max(cnd,arrival[EAST][east-1]);
			if (cnd<=irrTime[EAST][east-1]){
				printSelf("2.b",cnd);
				bst = min(bst,cnd);
			}
		}

		T[west][east][irritated][status]=bst;		
	}
};

int main(){
	scanf("%d %d\n",&time_to_pass,&n);
	REP(i,n){
		char c;
		int dir,a,irr;
		scanf("%c %d %d\n",&c,&a,&irr);
		if (c=='W') dir=WEST; else dir=EAST;
		arrival[dir][cnt[dir]]=a;
		irrTime[dir][cnt[dir]]=a+irr;
		cnt[dir]++;
	}
	
	REP(w,cnt[WEST]+1) REP(e,cnt[EAST]+1) REP(i,n+1) REP(s,2) T[w][e][i][s]=INF;
	REP(i,n+1) REP(s,2) T[0][0][i][s]=-time_to_wait;

	REP(w,cnt[WEST]+1) REP(e,cnt[EAST]+1) REP(i,n+1) REP(s,2) if (w+e>0) {
		State todo = State(s,w,e,i);
		todo.computeValue();
	}

	REP(i,n+1) REP(s,2) if (T[cnt[WEST]][cnt[EAST]][i][s]<INF) {
		printf("%d\n",i);
		return 0;
	}
	/* This should never happen */
	printf("-1\n");
	return 0;
}
