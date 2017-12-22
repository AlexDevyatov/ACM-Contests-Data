#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cstdint>
using namespace std;

#define MAXN 200000
struct dsu {int p,r,s; dsu():s(1){}} v[MAXN];
int findroot(int x){return v[x].p=(v[x].p==x? x: findroot(v[x].p));}
void join(int a,int b){
  if ((a=findroot(a))==(b=findroot(b))) return;
  if (v[a].r<v[b].r) swap(a,b);
  v[b].p=a, v[a].s+=v[b].s, ++v[a].r;
}
unordered_set<int> edge[MAXN];
int colour[MAXN];
void paint(int x,bool y){if (colour[x]!=y and ~colour[x]) cout<<"impossible\n",exit(0); else colour[x]=y;}

int main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  for (int i=n; i--;) colour[i]=-1, v[i].p=i;
  for (int i=m; i--;){
    int a,b,c; cin>>a>>b>>c;
    a--; b--;
    if (c==1){
      edge[a].insert(b);
      edge[b].insert(a);
    }
    else{
      paint(a,c);
      join(a,b);
    }
  }
  for (int i=n,k; k=-1, i--;)
    for (auto j: edge[i])
      if (~k) join(j,k); else k=j;
  for (int i=n; i--;)
    if (i!=findroot(i)){
      edge[v[i].p].insert(edge[i].begin(),edge[i].end());
      if (~colour[i]) paint(v[i].p,colour[i]);
    }
  for (int i=n; i--;)
    if (i==v[i].p)
      for (auto j: edge[i])
        if (v[j].p==i) paint(0,0), paint(0,1);
        else if (~colour[i]) paint(j,not colour[i]);

  int res=0;
  for (int i=n; i--;)
    if (i==v[i].p){
      if (colour[i]==0 or edge[i].empty() and !~colour[i]) continue;
      if (colour[i]==1) {res+=v[i].s; continue;}
      int j=v[*edge[i].begin()].p;
      if (make_pair(v[i].s,i)<make_pair(v[j].s,j)) res+=v[i].s;
    }
  cout<<res<<endl;
}
