/* Particle Swapping */
/* 01.10.2014 */
/* Marek Cygan */
/* O(nm log n) + O(n^2 log n) */

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

const int N = 510;
double dist[N][N];
int x[N], y[N];
int n;

int component[N][N]; //component id of a vertex in the new graph
double result[N][N];
VI kraw[N];
VPII t[N * N];

int main(){
  scanf("%d",&n);
  REP(i,n) scanf("%d %d",x+i,y+i);
  REP(i,n) REP(j,n) dist[i][j] = hypot(x[i]-x[j],y[i]-y[j]);
  int m;
  scanf("%d",&m);
  while (m--) {
    int a,b;
    scanf("%d %d",&a,&b);
    a--; b--;
    kraw[a].PB(b);
    kraw[b].PB(a);
  }
  REP(i,n) REP(j,n) {
    component[i][j] = i * n + j;
    t[i*n+j].PB(MP(i,j));
  }

  vector<pair<double,PII> > v;
  REP(i,n) REP(j,n) FOREACH(it,kraw[j]) {
    v.PB(MP(min(dist[i][j], dist[i][*it]), MP(i*n+j, i*n + *it)));
    v.PB(MP(min(dist[i][j], dist[i][*it]), MP(j*n+i, *it*n + i)));
  }
  sort(ALL(v));
  reverse(ALL(v));

  FOREACH(it2, v) {
    double d = it2->ST;
    int p0 = it2->ND.ST, p1 = it2->ND.ND;
    int i0 = p0 / n;
    int j0 = p0 % n;
    int i1 = p1 / n;
    int j1 = p1 % n;
    p0 = component[i0][j0];
    p1 = component[i1][j1];
    if (p0 == p1) continue;
    if (SIZE(t[p0]) > SIZE(t[p1])) swap(p0,p1);

    FOREACH(it,t[p0]) {
      if (component[it->ND][it->ST] == p1) {
        result[it->ND][it->ST] = result[it->ST][it->ND] = d;
      }
    }
    FOREACH(it,t[p0]) {
      component[it->ST][it->ND] = p1;
      t[p1].PB(*it);
    }
    t[p0].clear();
  }


  int q;
  scanf("%d",&q);
  while (q--) {
    int a,b;
    scanf("%d %d",&a,&b);
    a--; b--;
    printf("%.12lf\n", result[a][b]);
  }
  return 0;
}
