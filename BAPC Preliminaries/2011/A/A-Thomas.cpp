// Stifling the Mutiny
// Solution by Thomas Beuman

#include <cstdio>
using namespace std;

int main()
{ int runs, run, n, k, d;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &n, &k);
    if (n == 1) // Special case
      d = k/2;
    else if (n % 3) // n not divisible by 3
    { if (k <= n + n/3 + 1)
        d = k-n; // One loyal pirate on every ship, one disloyal pirate on every third ship
      else
        d = n/3 + 1 + (k - (n + n/3 + 1)) / 3; // Two loyal pirates on ship 1 and 2 for every extra disloyal pirate on ship 1
    }
    else // n divisible by 3
    { if (k <= n + n/3)
        d = k-n; // One loyal pirate on every ship, one disloyal pirate on every third ship
      else if (k <= n + n/3 + 2)
        d = k-n-1; // One extra loyal pirate on the penultimate ship, then one disloyal pirate on the last
      else
        d = n/3 + 1 + (k - (n + n/3 + 2)) / 3; // Two loyal pirates on ship 1 and 2 for every extra disloyal pirate on ship 1
    }
    printf("%d\n", d);
  }
  return 0;
}
