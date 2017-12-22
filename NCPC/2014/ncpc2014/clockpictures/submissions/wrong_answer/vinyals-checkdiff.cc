#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> VI;
const int TWOPI = 360000;

VI mkdiff(const VI& a, int d) {
  int n=a.size();
  VI ret(n);
  for (int i=0;i<n-d;++i) ret[i]=a[i+d]-a[i];
  for (int i=n-d;i<n;++i) ret[i]=a[i+d-n]+TWOPI-a[i];
  return ret;
}

bool check(const VI& a, const VI& b, int d) {
  VI da(mkdiff(a,d)), db(mkdiff(b,d));
  sort(da.begin(), da.end());
  sort(db.begin(), db.end());
  return da==db;
}

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  VI a(n), b(n);
  for(int& x : a) cin >> x;
  for(int& x : b) cin >> x;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  bool equal=true;
  for (int i=0; equal and i<20; ++i) {
    equal = check(a,b,rand()%(n/2)+1);
  }
  cout << (equal ? "possible" : "impossible") << endl;
}
