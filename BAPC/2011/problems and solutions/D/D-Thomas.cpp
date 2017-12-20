// Bad Wiring
// Solution by Thomas Beuman

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

bool OriginalStatus[100], NewStatus[100]; // The lights

int main()
{ int runs, run, n, D, i, j, s, start, flips, minflips;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &n, &D);
    for (i = 0; i < n; i++)
    { scanf("%d\n", &s);
      OriginalStatus[i] = !!s;
    }
    minflips = 999; // Least number of flips needed (999 = no solution)
    // Try all 2^D possible actions on the first D lights (or n, if n < D)
    for (start = (1 << min(D, n)) - 1; start >= 0; start--)
    { memcpy(NewStatus, OriginalStatus, n*sizeof(bool));
      flips = 0;
      for (i = 0; i < n; i++)
        // For the first D switches: flip as designated by variable start
        // For the others: flip if light i-D is still on
        if ((i < D && (start & (1 << i))) || (i >= D && NewStatus[i-D]))
        { flips++;
          for (j = max(0, i-D); j <= i + D && j < n; j++) // Flip the status of the lights
            NewStatus[j] ^= 1;
        }
      for (j = n-D; j < n && !NewStatus[j]; j++); // Check if the last D lights are out
      if (j == n)
        minflips = min(minflips, flips);
    }
    if (minflips == 999)
      printf("impossible\n");
    else
      printf("%d\n", minflips);
  }
  return 0;
}
