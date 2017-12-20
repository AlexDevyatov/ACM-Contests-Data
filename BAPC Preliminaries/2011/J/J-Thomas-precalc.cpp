// Shuriken Game
// Solution by Thomas Beuman

#include <cstdio>
using namespace std;

int WinningMove[101][100001]; // The unique winning move (or nomove, morethanone)
const int nomove = -1, morethanone = -2;

int main()
{ int runs, run, S, N, P, m;
  // Precalculate
  for (N = 2; N <= 100; N++)
  { // DP over the stacksize
    for (S = 0; S <= 100000; S++)
    { WinningMove[N][S] = nomove;
      // Try all moves
      for (m = 1; m <= N && m <= S; m++)
        if (WinningMove[N][S-m] == nomove || WinningMove[N][S-m] == m) // Move m wins if S-m has no winning move (besides m)
        { if (WinningMove[N][S] == nomove) // No winning move found yet
            WinningMove[N][S] = m;
          else
          { WinningMove[N][S] = morethanone;
            break; // No need to continue
          }
        }
    }
  }
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d\n", &S, &N, &P);
    if (WinningMove[N][S] == nomove || WinningMove[N][S] == P) // No winning move (besides P)
      printf("0\n");
    else if (WinningMove[N][S] == morethanone)
    { for (m = 1; m == P || (WinningMove[N][S-m] != nomove && WinningMove[N][S-m] != m); m++); // Find first winning move
      printf("%d\n", m);
    }
    else
      printf("%d\n", WinningMove[N][S]);
  }
  return 0;
}
