/* Road Work */
/* 30.09.2014 */
/* Marek Cygan */
/* O(n^3) DP, state: (#left, #right, #satisfied, direction) = min time*/

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

const int N = 260;
const int INF = 1001 * 1001 * 1001;

int t[N][N][N][2];
int arrival[2][N];
int patience[2][N];
int n1, n2;

int main() {
  int pass_time, n;
  char txt[10];
  scanf("%d %d",&pass_time,&n);
  REP(i,n) {
    int a, b;
    scanf("%s %d %d", txt, &a, &b);
    if (txt[0] == 'W') {
      arrival[0][n1] = a;
      patience[0][n1] = b;
      n1++;
    } else {
      arrival[1][n2] = a;
      patience[1][n2] = b;
      n2++;
    }
  }

  FOR(i,0,n) FOR(j,0,n) FOR(k,0,n) REP(dir,2) t[i][j][k][dir] = INF;
  t[0][0][0][0] = t[0][0][0][1] = 0;
  FOR(i,0,n) FOR(j,0,n) FOR(k,0,n) REP(dir,2) if (t[i][j][k][dir] < INF) {
    int x = t[i][j][k][dir];
    if (dir == 0 && i < n1) {
      int y = max(x, arrival[0][i]);
      int nk = k + (y-arrival[0][i] <= patience[0][i]);
      t[i+1][j][nk][dir] = min(t[i+1][j][nk][dir], y+3);
      t[i+1][j][nk][1-dir] = min(t[i+1][j][nk][1-dir], y+pass_time);
    }
    if (dir == 1 && j < n2) {
      int y = max(x, arrival[1][j]);
      int nk = k + (y-arrival[1][j] <= patience[1][j]);
      t[i][j+1][nk][dir] = min(t[i][j+1][nk][dir], y+3);
      t[i][j+1][nk][1-dir] = min(t[i][j+1][nk][1-dir], y+pass_time);
    }
  }

  int res = 0;
  FOR(i,0,n) FOR(j,0,n) FOR(k,0,n) REP(dir,2) if (t[i][j][k][dir] < INF) res = max(res, k);
  printf("%d\n", n-res);
  return 0;
}

