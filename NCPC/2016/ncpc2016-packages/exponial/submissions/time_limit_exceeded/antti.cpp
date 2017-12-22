#include <iostream>

using namespace std;

typedef long long ll;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b,a%b);
}

int phi(int x) {
    int u = 1;
    for (int i = 2; i*i <= x; i++) {
        int a = 0;
        while (x%i == 0) {
            x /= i;
            a++;
        }
        if (a > 0) {
            for (int j = 0; j < a-1; j++) u *= i;
            u *= (i-1);
        }
    }
    if (x > 1) u *= (x-1);
    return u;
}

int pow(int a, int b, int m) {
    if (b == 0) return 1;
    ll u = pow(a,b/2,m);
    u *= u;
    u %= m;
    if (b%2 == 1) u *= a;
    u %= m;
    return u;
}

int cyc(int n, int m) {
    ll n1 = n%m, n2 = n%m;
    n2 = (n2*n)%m;
    int c1 = 1, c2 = 2;
    while (true) {
        n1 = (n1*n)%m;
        c1++;
        n2 = (n2*n)%m;
        c2++;
        if (n1 == n2) return c2-c1;
        n2 = (n2*n)%m;
        c2++;
        if (n1 == n2) return c2-c1;
    }
}

int exp(int n, int m) {
    if (n == 1) return 1%m;
    if (n == 2) return 2%m;
    if (n == 3) return 9%m;
    if (n == 4) return 262144%m;
    if (n%m == 0) return 0;
    if (gcd(n,m) == 1) {
        int p = phi(m);
        return pow(n,exp(n-1,p),m);
    } else {
        int c = cyc(n,m);
        ll u = n;
        ll x = exp(n-1,c);
        for (int i = 0; ; i++) {
            x--;
            if (x < 0) x += c;
            if (u == (u*pow(n,c,m))%m) break;
            u = (u*n)%m;
        }
        return (u*pow(n,x,m))%m;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << exp(n,m) << "\n";
}

