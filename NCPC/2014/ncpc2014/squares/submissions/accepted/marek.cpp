/* How many squares */
/* 30.09.2014 */
/* Marek Cygan */
/* O(n^2) using doubles*/

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

const int N = 2100;
const double EPS = 1E-8;

PII wektor[N];
vector<pair<PII,PII> > v[N];
vector<double> dist[N];

inline int dot(PII p1, PII p2) {
  return p1.ST * p2.ND - p1.ND * p2.ST;
}

inline int scalar(PII p1, PII p2) {
  return p1.ST * p2.ST + p1.ND * p2.ND;
}

void give_ac(pair<PII,PII> p, double &a, double &c) {
  double x0 = p.ST.ST;
  double y0 = p.ST.ND;
  double x1 = p.ND.ST;
  double y1 = p.ND.ND;
  a = (y1-y0) / (x1-x0);
  c = y0 - a * x0;
}

int main() {
  int n;
  scanf("%d",&n);
  int g = 0;
  REP(foo,n) {
    int x0, y0, x1, y1;
    scanf("%d %d %d %d",&x0,&y0,&x1,&y1);
    int a = x1-x0;
    int b = y1-y0;
    int which = -1;
    REP(i,g) if (dot(wektor[i],MP(a,b)) == 0) {
      which = i;
      break;
    }
    if (which == -1) {
      wektor[g] = MP(a,b);
      which = g++;
    }
    v[which].PB(MP(MP(x0,y0),MP(x1,y1)));
  }

  REP(i,g) {
    dist[i].reserve(SIZE(v[i]) * SIZE(v[i]) / 2);
    REP(a, SIZE(v[i])) REP(b,a) {
      if (wektor[i].ST == 0) {
        dist[i].PB(abs(v[i][a].ST.ST - v[i][b].ST.ST));
      } else {
        double a1, b1 = 1.0, c1;
        double a2, b2 = 1.0, c2;
        give_ac(v[i][a], a1, c1);
        give_ac(v[i][b], a2, c2);
        double d = fabs(c1-c2) / sqrt(a1 * a1 + b1 * b1);
        dist[i].PB(d);
      }
    }
    sort(ALL(dist[i]));
  }

  LL res = 0;
  REP(i,g) REP(j,i) if (scalar(wektor[i],wektor[j]) == 0) {
    int a = 0, b = 0;
    while (a < SIZE(dist[i]) && b < SIZE(dist[j])) {
      if (dist[i][a] + EPS < dist[j][b]){ 
        a++;
        continue;
      }
      if (dist[j][b] + EPS < dist[i][a]) {
        b++;
        continue;
      }
      double x = dist[i][a];
      int c1 = 0, c2 = 0;
      while (a < SIZE(dist[i]) && fabs(dist[i][a]-x) < EPS) a++, c1++;
      while (b < SIZE(dist[j]) && fabs(dist[j][b]-x) < EPS) b++, c2++;
      res += (LL)c1 * c2;
    }
  }
  printf("%lld\n", res);
  return 0;
}

