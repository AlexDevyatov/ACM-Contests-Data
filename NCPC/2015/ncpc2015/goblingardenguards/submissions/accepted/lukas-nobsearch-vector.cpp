//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

const int length = 10001;
double pytag(double r, double x)
{
    return sqrt(r * r - x * x);
}
int main()
{
    int n, q;
    scanf("%d", &n);
    vector<vector<int>> columns(length);

    int x, y;
    rep(i,0,n)
    {
        scanf("%d %d", &x, &y);
        columns[x].push_back(y);
    }

    rep(i,0,(int)length)
        sort(columns[i].begin(), columns[i].end());

    scanf("%d", &q);
    rep(i,0,q)
    {
        int r;
        scanf("%d %d %d", &x, &y, &r);
        for (int j = max(0, x - r); j <= x + r; j++)
            if ((size_t)j < columns.size() && !columns[j].empty())
            {
                int d = abs(x - j);
                int up = floor(y + pytag(r, d));
                int down = ceil(y - pytag(r, d));
                auto it = columns[j].begin();
                while (it != columns[j].end() && *it < down) it++;
                auto first = it;
                while (it != columns[j].end() && *it <= up) it++;
                columns[j].erase(first, it);
            }
    }

   cout << accumulate(columns.begin(), columns.end(), 0,
           [](int& a, vector<int> b) { return a + b.size();} ) << endl;
}
