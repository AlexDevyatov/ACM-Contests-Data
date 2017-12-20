// Shuriken Game
// Solution by Thomas Beuman

#include <cstdio>
using namespace std;

int WinningMove[100001]; // The unique winning move (or nomove, morethanone)
const int nomove = -1, morethanone = -2;

int main()
{ int runs, run, S, N, P, s, m;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d\n", &S, &N, &P);
    // DP over the stacksize
    for (s = 0; s <= S; s++)
    { WinningMove[s] = nomove;
      // Try all moves
      for (m = 1; m <= N && m <= s; m++)
        if (WinningMove[s-m] == nomove || WinningMove[s-m] == m) // Move m wins if s-m has no winning move (besides m)
        { if (WinningMove[s] == nomove) // No winning move found yet
            WinningMove[s] = m;
          else
          { WinningMove[s] = morethanone;
            break; // No need to continue
          }
        }
    }
    if (WinningMove[S] == nomove || WinningMove[S] == P) // No winning move (besides P)
      printf("0\n");
    else if (WinningMove[S] == morethanone)
    { for (m = 1; m == P || (WinningMove[S-m] != nomove && WinningMove[S-m] != m); m++); // Find first winning move
      printf("%d\n", m);
    }
    else
      printf("%d\n", WinningMove[S]);
  }
  return 0;
}
