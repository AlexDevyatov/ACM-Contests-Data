#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef unordered_set<int> HI;
typedef vector<HI> VHI;
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

int radius(const VVI& g, const VI& component) {
  QI leaves,newleaves;
  VHI gg(g.size());
  for (int i : component) {
    gg[i]=HI(g[i].begin(), g[i].end());
    if (gg[i].size()==1) leaves.push(i);
  }
  int ans=0;
  while (not leaves.empty()) {
    if (gg[leaves.front()].size()==0) break;
    ++ans;
    QI newleaves;
    while (not leaves.empty()) {
      int i=leaves.front();leaves.pop();
      for (int j : gg[i]) {
        gg[j].erase(i);
        if (gg[j].size()==1) newleaves.push(j);
      }
      gg[i].clear();
    }
    swap(leaves,newleaves);
  }
  return ans;
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
  for (int i=0;i<c;++i) {
    VI component;
    dfs(g,seen,component,i);
    radii.push_back(radius(g,component));
  }
  sort(radii.begin(), radii.end(), greater<int>());
  for (int r : radii) cerr << r << ' '; cerr << endl;
  int ans = 1 + radii[0] + radii[1];
  if (radii.size()>2) ans = max(ans, 2 + radii[1] + radii[2]);
  cout << ans << endl;
}
