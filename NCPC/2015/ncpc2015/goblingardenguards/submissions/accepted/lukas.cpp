//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <set>
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
    vector<multiset<int>> columns(length);

    int x, y;
    rep(i,0,n)
    {
        scanf("%d %d", &x, &y);
        columns[x].insert(y);
    }

    scanf("%d", &q);
    rep(i,0,q)
    {
        int r;
        scanf("%d %d %d", &x, &y, &r);
        for (int j = max(0, x - r); j <= x + r; j++)
            if ((size_t)j < columns.size() && !columns[j].empty())
            {
                int d = abs(x - j);
                double up = y + pytag(r, d);
                columns[j].erase(
                        columns[j].lower_bound((int)ceil(2 * y - up)),
                        columns[j].upper_bound(floor(up))
                    );
            }
    }

   cout << accumulate(columns.begin(), columns.end(), 0,
           [](int& a, multiset<int> b) { return a + b.size();} ) << endl;
}
