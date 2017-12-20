// Shuriken Game
// Faulty solution (too slow) by Thomas Beuman

#include <cstdio>
using namespace std;

bool Lost[100001][101]; // True if the position is losing for the player to move

int main()
{ int runs, run, S, N, P, s, m, p;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d\n", &S, &N, &P);
    // DP over the stacksize and the previous move
    for (s = 0; s <= S; s++)
      for (p = 1; p <= N; p++)
      { Lost[s][p] = true;
        for (m = 1; m <= N && m <= s; m++)
          if (m != p && Lost[s-m][m]) // Check if m is a winning move
          { Lost[s][p] = false;
            break;
          } 
      }
    if (Lost[S][P])
      printf("0\n");
    else
    { for (m = 1; m == P || !Lost[S-m][m]; m++); // Find first winning move
      printf("%d\n", m);
    }
  }
  return 0;
}
