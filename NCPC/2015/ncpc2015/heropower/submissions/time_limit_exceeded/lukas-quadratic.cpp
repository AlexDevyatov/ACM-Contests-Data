//Solution by lukasP (Lukáš Poláček)
//Complexity O(n^2)
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef vector<int> vi;
void improveMax(int &a, int b)
{
    a = max(a, b);
}
int main()
{
    int n, p;
    scanf("%d %d", &n, &p);

    unordered_map<int, int> ord;
    vi t(n);
    rep(i,0,n) {
        scanf("%d", &t[i]);
        ord[t[i]] = i;
    }

    vi totpow;
    vector<bool> first(n, false);
    rep(i,0,p)
    {
        int s, e; scanf("%d %d", &s, &e);
        totpow.resize(ord[s] + 1, (totpow.empty() ? 0 : totpow.back()));
        rep(j,ord[s],ord[e])
            totpow.push_back(totpow.back() + t[j + 1] - t[j]);
        first[ord[s]] = true;
    }
    totpow.resize(n, totpow.back());

    int best[n + 1][2]; // (i, j) the best solution using the first i notes and draining or not (j)
    memset(best, 0, sizeof(best));
    rep(i,0,n)
    {
        int point = i;
        rep(j,point+1,n)
        {
            while (point + 1 <= j && totpow[point + 1] - totpow[i] <= t[j] - t[point + 1])
                point++;
            improveMax(best[j][1], best[i][0] + (j - point));
        }
        rep(l,0,2) improveMax(best[i + 1][l], best[i][l]); // don't do anything
        if (first[i + 1]) // the first one in an SP phrase
            improveMax(best[i + 1][0], best[i][1]);
    }
    cout << max(best[n][0], best[n][1]) + n << endl;
}
