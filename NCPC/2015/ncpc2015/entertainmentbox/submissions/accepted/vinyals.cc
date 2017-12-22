#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int,int> PII;
typedef vector<PII> VP;
typedef multiset<int,greater<int>> SI;

int main() {
  int n,k;
  cin >> n >> k;
  VP shows(n);
  for (auto& x : shows) cin >> x.first >> x.second;
  sort(shows.begin(), shows.end(), [] (const PII& p, const PII& q) {
      return p.second < q.second;
    });
  int ans=0;
  SI endtimes;
  for (const auto& x : shows) {
    auto it = endtimes.lower_bound(x.first);
    if (it!=endtimes.end()) endtimes.erase(it);
    if (endtimes.size()<k) {
      endtimes.insert(x.second);
      ++ans;
    }
  }
  cout << ans << endl;
}
