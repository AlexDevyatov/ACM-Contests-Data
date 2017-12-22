#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>
using namespace std;

#define rep(i,a,b) for(auto i=a; i<(b); ++i)

typedef vector<int> vi;
vector<vi> gen(int n)
{
    if (n == 1) return vector<vi> (1, vi(1, 1));
    vector<vi> next = gen(n - 1);

    vector<vi> res;
    bool dir = false;
    for (vi &o : next)
    {
        if (!dir) o.push_back(n);
        else o.insert(o.begin(), n);
        res.push_back(o);

        int cur = dir ? 0 : n - 1;
        rep(i,0,n-1)
        {
            int pos = cur + (dir ? 1 : -1);
            swap(o[cur], o[pos]);
            cur = pos;
            res.push_back(o);
        }
        dir = !dir;
    }
    return res;
}
int main()
{
    int n;
    scanf("%d", &n);

    vector<vi> res = gen(n);
    for (vi &o : res)
    {
        rep(i,0,n-1) cout << o[i] << " ";
        cout << o.back() << endl;
    }
}
