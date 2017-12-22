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

#define MAX 1300

int n,c,k;

int mn[MAX];
int mx[MAX]; 
int color[MAX];
bool T[MAX];

vector<int> input;

int process(int v,int d){
	if (color[v]!=0){
		if (color[v]<0){
			c++;
			mx[c]=0;
			mn[c]=d+color[v];
			return c;
		} else {
			return color[v];
		}
	} else {
		color[v]=-d;
		int r=process(input[v],d+1);
		color[v]=r;		
		mx[r]++;
		return r;
	}
}

int main(){
	scanf("%d%d",&n,&k);
	REP(i,n){
		int a;
		scanf("%d",&a); a--;
		input.PB(a);
		mn[i]=mx[i]=color[i]=0;
	}
	c=0;
	REP(i,n) process(i,1);

	T[0]=true;
	FOR(i,1,c) FORD(j,n,0) FOR(t,mn[i],mx[i]){
		if (j-t>=0 && T[j-t]) T[j]=true;
	}

	FORD(j,k,0) if (T[j]){printf("%d\n",j); return 0;}

	return 0;
}

