//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <bitset>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

int main()
{
    int f; scanf("%d", &f);
    rep(cas,0,f)
    {
        int t, n;
        scanf("%d %d", &t, &n);
        bitset<10001> can, ncan, mask;
        rep(i,0,t+1) mask[i] = true;
        can = mask;

        rep(i,0,n)
        {
            int start, end;
            scanf("%d %d", &start, &end);
            const int dif = end - start;
            ncan = (can << dif) | (can >> dif);
            ncan = ncan & mask;

            swap(ncan, can);
        }
        if (can.count() == 0)
        {
            cout << "impossible" << endl;
            return 0;
        }
    }
    cout << "possible" << endl;
}
