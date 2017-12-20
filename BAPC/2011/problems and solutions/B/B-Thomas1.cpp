// Quick out of the Harbour
// Solution in O(hw) by Thomas Beuman

#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

#define pii pair<int, int>
#define mpii make_pair<int, int>

char Map[500][500];
queue<pii> BFS[52]; // Breadth first search queues, one for every time-index modulo D+2
int MinimumTime[500][500];

int main()
{ int runs, run, h, w, d, x, y, x2, y2, i, t, t2;
  int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d\n", &h, &w, &d);
    for (i = 0; i < d+2; i++)
      BFS[i] = queue<pii>();
    memset(MinimumTime, 127, sizeof(MinimumTime)); // Initialize to "infinity"
    for (y = 0; y < h; y++)
    { for (x = 0; x < w; x++)
      { scanf("%c", &Map[x][y]);
        if (Map[x][y] == 'S')
        { MinimumTime[x][y] = 0;
          BFS[0].push(mpii(x, y)); // Put the initial position in the first BFS queue
        }
      }
      scanf("\n");
    }
    t = 0; // Time
    while (true)
    { // Get next position
      x = BFS[t%(d+2)].front().first;
      y = BFS[t%(d+2)].front().second;
      t2 = t + (Map[x][y] == '@' ? 1+d : 1); // Time of arrival at adjacent point
      if (x == 0 || x == w-1 || y == 0 || y == h-1) // Exit found
      { t = t2;
        break;
      }
      BFS[t%(d+2)].pop();
      if (MinimumTime[x][y] == t) // Check if this point hasn't been processed yet
      { for (i = 0; i < 4; i++)
        { x2 = x + dx[i];
          y2 = y + dy[i];
          if ((Map[x2][y2] == '.' || Map[x2][y2] == '@') && MinimumTime[x2][y2] > t2) // No (shorter) path found yet
          { MinimumTime[x2][y2] = t2;
            BFS[t2 % (d+2)].push(mpii(x2, y2));
          }
        }
      }
      for (i = 0; i < d+2 && BFS[(t+i)%(d+2)].empty(); i++); // Find next non-empty BFS queue
      if (i == d+2)
      { printf("Exit unreachable!\n");
        break;
      }
      t += i;
    }
    printf("%d\n", t);
  }
  return 0;
}
