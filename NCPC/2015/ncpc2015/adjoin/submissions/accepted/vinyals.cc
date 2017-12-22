#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef queue<int> QI;

void dfs(const VVI& g, VI& seen, VI& out, int i) {
  if (seen[i]) return;
  seen[i]=true;
  out.push_back(i);
  for (int j : g[i]) {
    if (seen[j]) continue;
    dfs(g,seen,out,j);
  }
}

int diameter(const VVI& gg, const VI& component, VI& degree) {
  QI leaves,newleaves;
  for (int i : component) {
    degree[i]=gg[i].size();
    if (degree[i]==1) leaves.push(i);
  }
  int ans=0;
  while (not leaves.empty()) {
    if (degree[leaves.front()]==0) return 2*ans;
    ++ans;
    QI newleaves;
    while (not leaves.empty()) {
      int i=leaves.front();leaves.pop();
      for (int j : gg[i]) {
        if (--degree[j]==0) continue;
        if (degree[j]==1) newleaves.push(j);
      }
    }
    swap(leaves,newleaves);
  }
  return 2*ans-1;
}

int main() {
  int c,l;
  cin >> c >> l;
  VVI g(c);
  for (int i=0;i<l;++i) {
    int a,b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  VI seen(c,false);
  VI radii;
  int ans=0;
  VI degree(c);
  for (int i=0;i<c;++i) {
    VI component;
    dfs(g,seen,component,i);
    if (component.empty()) continue;
    int diam = diameter(g,component,degree);
    cerr << diam << endl;
    ans = max(ans,diam);
    radii.push_back((diam+1)/2);
  }
  sort(radii.begin(), radii.end(), greater<int>());
  ans = max(ans, 1 + radii[0] + radii[1]);
  if (radii.size()>2) ans = max(ans, 2 + radii[1] + radii[2]);
  cout << ans << endl;
}
