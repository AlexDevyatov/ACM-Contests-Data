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

int n;

vector<int> input; 

int main(){
	scanf("%d",&n);
	REP(i,n){
		int a;
		scanf("%d",&a);
		input.PB(a);
	}
	sort(input.begin(),input.end());
	int res=n;
	REP(i,n){
		int cand = input[i]+(n-i-1);
		if (cand<res) res=cand;
	}
	printf("%d\n",res);
	return 0;
}

