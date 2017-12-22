#include <cstdio>
#include <set>

using namespace std;

const int GRID_SIZE = 10000;

int main()
{
    int g;
    scanf("%d", &g);
    multiset<int> goblins[GRID_SIZE + 1];
    for (int i = 0; i < g; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        goblins[x].insert(y);
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        int x, y, r;
        scanf("%d%d%d", &x, &y, &r);
        for (int sx = max(0, x - r); sx <= min(GRID_SIZE, x + r); ++sx)
        {
            int minY = GRID_SIZE + 1;
            int maxY = -1;
            for (int sy = max(0, y - r); sy <= min(GRID_SIZE, y + r); ++sy)
                if ((sx-x)*(sx-x) + (sy-y)*(sy-y) <= r*r)
                {
                    minY = min(minY, sy);
                    maxY = max(maxY, sy);
                }

            //printf("minY=%d, maxY=%d\n", minY, maxY);
            auto lb = goblins[sx].lower_bound(minY);
            auto ub = goblins[sx].upper_bound(maxY);
            goblins[sx].erase(lb, ub);
        }
    }

    int sum = 0;
    for (int i = 0; i <= GRID_SIZE; ++i)
        sum += goblins[i].size();

    printf("%d\n", sum);

    return 0;
}
