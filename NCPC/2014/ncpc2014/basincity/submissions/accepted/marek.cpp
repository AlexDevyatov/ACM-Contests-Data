/* Basin City Surveillance */
/* 30.09.2014 */
/* Marek Cygan */
/* T(k) = T(k-1) + 6T(k-2) */

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

typedef vector <int > VI;
typedef vector < VI > VVI;
typedef long long LL;
typedef vector < LL > VLL;
typedef vector < double > VD;
typedef vector < string > VS;
typedef pair<int,int> PII;
typedef vector <PII> VPII;
typedef istringstream ISS;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<(n); ++i)
#define FOR(var,pocz,koniec) for (int var=(pocz); var<=(koniec); ++var)
#define FORD(var,pocz,koniec) for (int var=(pocz); var>=(koniec); --var)
#define FOREACH(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second
#define SIZE(x) (int)x.size()

const int N = 110;
VI kraw[N];
int t[N][N];
int used[N];
int n;

int go(int i, int k) {
  if (k <= 0) return 1;
  if (i >= n) return 0;
  if (used[i]) return go(i+1,k);
  VI v;
  used[i] = 1;
  FOREACH(it, kraw[i]) if (!used[*it]){
    v.PB(*it);
    used[*it] = 1;
  }
  if (go(i+1,k-1)) return 1;
  FOREACH(it,v) used[*it] = 0;
  VI v2;
  REP(a,SIZE(v)) REP(b, a) if (!t[v[a]][v[b]]) {
    used[v[a]] = 1;
    used[v[b]] = 1;
    FOREACH(it, kraw[v[a]]) if (!used[*it]) v2.PB(*it);
    FOREACH(it, kraw[v[b]]) if (!used[*it]) v2.PB(*it);
    
    FOREACH(it,v2) used[*it] = 1;
    if (go(i+1,k-2)) return 1;
    FOREACH(it,v2) used[*it] = 0;
    v2.clear();
    used[v[a]] = 0;
    used[v[b]] = 0;
  }
  used[i] = 0;
  return 0;
}

int main(){
  int k;
  scanf("%d %d",&k,&n);
  if (n >= 5 * k) {
    puts("possible");
    return 0;
  }
  REP(i,n) {
    int x;
    scanf("%d",&x);
    while (x--) {
      int y;
      scanf("%d",&y);
      kraw[i].PB(--y);
      t[i][y] = 1;
    }
  }
  puts(go(0,k) ? "possible" : "impossible");
  return 0;
}
