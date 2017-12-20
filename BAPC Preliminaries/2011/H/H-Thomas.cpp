// Stealth Ninja
// Solution by Thomas Beuman

#include <cstdio>
#include <cstring>
using namespace std;

bool Available[1000][1000][8]; // True if this square is empty and not watched by a guard at this time index
bool Reachable[1000][1000][8]; // True if the ninja can reach this position at this time index
int BFS[3000000][3]; // Breadth first search list

int main()
{ int runs, run, n, k, g, i, j, x, y, t, x2, y2, t2, cur, last;
  int dx[5] = {0, 1, 0, -1, 0}, dy[5] = {0, 0, 1, 0, -1};
  char c;
  bool succeeds;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &n, &k);
    memset(Available, true, sizeof(Available));
    for (g = 0; g < k; g++)
    { scanf("%d %d %c\n", &y, &x, &c);
      j = (c == 'B' ? 0 : (c == 'R' ? 2 : (c == 'F' ? 4 : 6)));
      // Determine the squares the guard sees
      for (t = 0; t < 2; t++)
      { for (i = y; i < 2*n; i++) // Looking to the back
          Available[x][i][(8-j)%8 + t] = false;
        for (i = x; i < 2*n; i++) // Looking to the right
          Available[i][y][(10-j)%8 + t] = false;
        for (i = y; i > 0; i--) // Looking to the front
          Available[x][i][(12-j)%8 + t] = false;
        for (i = x; i > 0; i--) // Looking to the left
          Available[i][y][(14-j)%8 + t] = false;
      }
    }
    for (x = 2; x < 2*n; x += 2)
      for (y = 2; y < 2*n; y += 2)
        for (t = 0; t < 8; t++)
          Available[x][y][t] = false; // Support column
    memset(Reachable, false, sizeof(Reachable));
    last = 0;
    // Put all available squares behind the curtains in the BFS list
    for (x = 1; x < 2*n; x += 2)
      for (t = 0; t < 8; t++)
      { Reachable[x][0][t] = true;
        BFS[last][0] = x;
        BFS[last][1] = 0;
        BFS[last][2] = t;
        last++;
      }
    succeeds = false;
    for (cur = 0; !succeeds && cur < last; cur++)
    { // Get next square and time
      x = BFS[cur][0];
      y = BFS[cur][1];
      t = BFS[cur][2];
      t2 = (t+1) % 8; // Next time index
      for (k = 0; k < 5; k++) // For all possible moves
      { x2 = x + dx[k];
        y2 = y + dy[k];
        if (y2 == 2*n && x2%2 == 1) // Behind a curtain on the other side of the hall
        { succeeds = true;
          break;
        }
        if (x2 > 0 && x2 < 2*n && y2 > 0 && y2 < 2*n && Available[x2][y2][t2] && !Reachable[x2][y2][t2])
        { // Add to BFS-list
          Reachable[x2][y2][t2] = true;
          BFS[last][0] = x2;
          BFS[last][1] = y2;
          BFS[last][2] = t2;
          last++;
        }
      }
    }
    printf("%s\n", succeeds ? "succeeds" : "fails");
  }
  return 0;
}
