#include <bits/stdc++.h>

typedef long long ll;

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

ll phi(ll m) {
  ll res = 1;
  for (ll p = 2; p*p <= m; ++p) {
    if (m % p == 0) {
      res *= p-1;
      m /= p;
      while (m % p == 0) {
	res *= p;
	m /= p;
      }
    }
  }
  if (m > 1) {
    res *= m-1;
  }
  return res;
}

ll expmod(ll b, ll e, ll m) {
  ll res = 1;
  while (e) {
    if (e & 1) res = (res * b) % m;
    e /= 2;
    b = (b*b) % m;
  }
  return res;
}

ll expo_trunc(ll n) {
  return n < 4 ? n < 3 ? n : 9 : 100000;
}

ll expo_mod_m(ll n, ll m) {
  if (m == 1) return 0;
  if (n == 1) return 1;
  ll a = gcd(n, m);
  return expmod(a, expo_trunc(n-1), m)*expmod(n/a, expo_mod_m(n-1, phi(m)), m) % m;
}

int main(void) {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    printf("%lld\n", expo_mod_m(n, m));
  }
}
