// Quick out of the Harbour
// Solution in O(hwd) by Thomas Beuman

#include <cstdio>
#include <cstring>
using namespace std;

char Map[500][500];
int BFS[500*500*51][3]; // Breadth first search queue (position and waiting time)
bool Seen[500][500]; // Already in queue

int main()
{ int runs, run, h, w, d, x, y, z, x2, y2, i, t, cur, lim, last;
  int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d\n", &h, &w, &d);
    memset(Seen, false, sizeof(Seen));
    for (y = 0; y < h; y++)
    { for (x = 0; x < w; x++)
      { scanf("%c", &Map[x][y]);
        if (Map[x][y] == 'S') // Put the initial position in the BFS queue
        { BFS[0][0] = x;
          BFS[0][1] = y;
          BFS[0][2] = 0;
          Seen[x][y] = true;
        }
      }
      scanf("\n");
    }
    t = 1; // Time
    last = lim = 1;
    for (cur = 0; cur < last; cur++)
    { if (cur == lim)
      { t++;
        lim = last; // The last location which can be reached in time t
      }
      // Get next position
      x = BFS[cur][0];
      y = BFS[cur][1];
      z = BFS[cur][2]; // Time (left) to wait
      if (z > 0)
      { BFS[last][0] = x;
        BFS[last][1] = y;
        BFS[last][2] = z-1;
        last++;
        continue;
      }
      if (x == 0 || x == w-1 || y == 0 || y == h-1) // Exit found
        break;
      for (i = 0; i < 4; i++)
      { x2 = x + dx[i];
        y2 = y + dy[i];
        if ((Map[x2][y2] == '.' || Map[x2][y2] == '@') && !Seen[x2][y2])
        { Seen[x2][y2] = true;
          BFS[last][0] = x2;
          BFS[last][1] = y2;
          BFS[last][2] = (Map[x2][y2] == '@' ? d : 0);
          last++;
        }
      }
    }
    printf("%d\n", t);
  }
  return 0;
}
