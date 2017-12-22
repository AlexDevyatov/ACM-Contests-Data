#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

typedef long long ll;
typedef vector<pair<ll,ll>> VII;

ll powmod(ll x, ll y, ll m) {
  if (y==0) return 1;
  if (y==1) return x%m;
  ll xx=powmod(x,y/2,m);
  xx=xx*xx%m;
  if (y&1) xx=xx*x%m;
  return xx;
}

VII factor(ll x) {
  VII ret;
  for (ll p=2;p*p<=x;++p) {
    if (x%p==0) {
      x/=p;
      ll pk=1;
      while(x%p==0) {
        pk*=p;
        x/=p;
      }
      ret.push_back({p,pk});
    }
  }
  if (x>1) ret.push_back({x,1});
  return ret;
}

ll phi(ll x) {
  ll ret=1;
  for (const auto& ppk : factor(x)) {
    ll p,pk;
    tie(p,pk)=ppk;
    ret*=(p-1)*pk;
  }
  return ret;
}

ll exponial(ll n, ll m) {
  //  cerr << "exp " << n << ' ' << m << endl;
  if (m==1) return 0;
  n%=m;
  if (n<2) return n;
  ll p=phi(m);
  return powmod(n,exponial(n-1,p),m);
}

int main () {
  ll n,m;
  cin >> n >> m;
  cout << exponial(n,m) << endl;
}
