//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int main() {
    int n; scanf("%d", &n);
    vector<unsigned> a(n);
    rep(i,0,n) scanf("%d", &a[i]);

    unsigned money = 100 % a[0], stocks = 100 / a[0];
    unsigned prev = a[0];
    unsigned ma = money + stocks * a[0];

    rep(i,1,n) {
        if (a[i] < prev) { // Sell
            money += prev * stocks;

            unsigned count = min(100000u, money / a[i]);
            stocks = count;
            money = money - count * a[i];
        }
        prev = a[i];
        ma = max(ma, money + stocks * a[i]);
    }

    cout << ma << endl;
}
