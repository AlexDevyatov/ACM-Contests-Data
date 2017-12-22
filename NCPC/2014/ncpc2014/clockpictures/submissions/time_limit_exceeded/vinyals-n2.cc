#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdint>
using namespace std;

typedef vector<int32_t> VI;
const int TWOPI = 360000;

int n;

VI mkdiff(const VI& a, int d) {
  VI ret(n);
  for (int i=0;i<n-d;++i) ret[i]=a[i+d]-a[i];
  for (int i=n-d;i<n;++i) ret[i]=a[i+d-n]+TWOPI-a[i];
  return ret;
}

bool check(const VI& da, const VI& db, int d) {
  return memcmp(&da[0],&db[d],n*sizeof(int32_t))==0;
}

bool check(const VI& a, const VI& b) {
  VI da(mkdiff(a,1)), db(mkdiff(b,1));
  db.resize(2*n);
  for (int i=0;i<n;++i) db[i+n]=db[i];
  for (int d=0;d<n;++d) if (check(da, db, d)) return true;
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  VI a(n), b(n);
  for(int& x : a) cin >> x;
  for(int& x : b) cin >> x;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  bool equal=check(a,b);
  cout << (equal ? "possible" : "impossible") << endl;
}
