//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
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
        vector<bool> can(t + 1, true);
        vector<bool> ncan = can;

        rep(i,0,n)
        {
            int start, end;
            scanf("%d %d", &start, &end);
            const int dif = end - start;

            fill(ncan.begin(), ncan.end(), 0);
            rep(j,0,t+1) if (can[j])
            {
                if (j >= dif)
                    ncan[j - dif] = true;
                if (j + dif <= t)
                    ncan[j + dif] = true;
            }
            swap(ncan, can);
        }
        auto is_false = [](bool const x) { return !x; };
        if (all_of(can.begin(), can.end(), is_false))
        {
            cout << "impossible" << endl;
            return 0;
        }
    }
    cout << "possible" << endl;
}
