//Solution by lukasP (Lukáš Poláček)
//Rolling hash without sorting
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
ll mod = 326932427;
ll po = 41351;
const ll cyc = 360000;
ll read_normalize(int n)
{
    vector<ll> x(n), y(n);
    rep(i,0,n) scanf("%lld", &x[i]);

    ll hash = 0, big = 1;
    rep(i,0,n)
    {
        y[i] = (x[(i + 1) % n] - x[i] + cyc) % cyc;
        hash = (hash * po + y[i]) % mod;
        big = big * po % mod;
    }

    big = (mod + 1 - big) % mod;
    ll res = hash;
    rep(i,0,n)
    {
        hash = (hash * po + big * y[i]) % mod;
        res = min(res, hash);
    }
    return res;
}
int main()
{
    int n; scanf("%d", &n);
    ll a = read_normalize(n);
    ll b = read_normalize(n);
    cout << ((a == b) ? "possible" : "impossible") << endl;
}
