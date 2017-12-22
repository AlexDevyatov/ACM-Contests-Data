#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
#define MAXN 500

pair<ld,int> by_cost[MAXN*MAXN];
vector<int> tree[MAXN*MAXN],edge[MAXN];

/**
 * Author
 *   Robin Lee (hex539)
 *
 * Solution
 *   Make a forest of vertices with labels of states (x,y) with weights set to
 *   their distance and infinite-weight edges to other states reachable from
 *   there. Construct a maximum spanning forest - the answer to each query (x,y)
 *   the largest weight on the path between (x,y) and (y,x)
 *
 * Complexity
 *   O(N^2 logN)
 */

ld c[MAXN*MAXN][18];
bool did[MAXN*MAXN];
int d[MAXN*MAXN],p[MAXN*MAXN][18];
void build(int x,int r=-1){
  did[x]=~(p[x][0]=(~r?r:x));
  for (int i=1; i<18; i++)
    p[x][i]=p[p[x][i-1]][i-1],
    c[x][i]=min(c[x][i-1],c[p[x][i-1]][i-1]);
  for (auto y: tree[x])
    if (not did[y])
      d[y]=d[x]+1,build(y,x);
}

struct uf {int p,r;} v[MAXN*MAXN];
int fr(int x){return v[x].p==x? x: v[x].p=fr(v[x].p);}
bool join(int a,int b){
  if ((a=fr(a))==(b=fr(b))) return false;
  if (v[a].r<v[b].r) swap(a,b);
  return v[b].p=a, ++v[a].r;
}

int main(){
  cout<<fixed;
  cout.precision(10);
  ios::sync_with_stdio(false);

  // read in coordinates
  int n; cin>>n;
  {
    vector<ld> x(n),y=x;
    for (int i=0; i<n; i++) cin>>x[i]>>y[i];
    for (int i=n; i--;)
      for (int j=n; j--;){
        by_cost[i*n+j]={hypotl(x[i]-x[j],y[i]-y[j]), i*n+j},
        c[i*n+j][0]=by_cost[i*n+j].first;
        v[i*n+j].p=i*n+j;
      }
  }
  // read in edges
  int m; cin>>m;
  {
    for (int i=m; i--;)
      {int a,b; cin>>a>>b; --a,--b; edge[a].push_back(b); edge[b].push_back(a);}
  }

  // add each vertex to the tree in descending cost order
  sort(by_cost,by_cost+n*n);
  for (int i=n*n; i--;){
    int x=by_cost[i].second;
    int a=x/n, b=x%n;
    for (auto y: edge[a]){
      if (c[y*n+b][0]>=c[a*n+b][0] and join(a*n+b, y*n+b)){
        tree[a*n+b].push_back(y*n+b);
        tree[y*n+b].push_back(a*n+b);
      }
    }
    for (auto y: edge[b]){
      if (c[a*n+y][0]>=c[a*n+b][0] and join(a*n+b, a*n+y)){
        tree[a*n+b].push_back(a*n+y);
        tree[a*n+y].push_back(a*n+b);
      }
    }
  }

  // construct tree pointers
  for (int i=n*n; i--;)
    if (not did[i])
      build(i);

  // read in and answer queries
  int l; cin>>l;
  for (int i=0; i<l; i++){
    int x,y; cin>>x>>y; --x,--y;
    int a=x*n+y,b=y*n+x;
    if (d[a]>d[b]) swap(a,b);
    ld ans=c[a][0];
    for (int l=18; l--;)
      if (d[b]-(1<<l)>=d[a])
        ans=min(ans, c[b][l]), b=p[b][l];
    for (int l=18; l--;)
      if (p[a][l]!=p[b][l])
        ans=min(ans, min(c[a][l], c[b][l])),  a=p[a][l], b=p[b][l];
    for (;;){
      ans=min(ans, min(c[a][0], c[b][0]));
      if (a==b) break;
      a=p[a][0];
      b=p[b][0];
    }
    cout<<ans<<endl;
  }
}
