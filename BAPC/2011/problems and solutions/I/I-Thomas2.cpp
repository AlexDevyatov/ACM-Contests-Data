// Parking Ships
// Solution in O(N^2) by Thomas Beuman

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long alot = 10000000000ll;

struct pirate
{ long long house, shiplength;
};

bool operator < (const pirate& a, const pirate& b)
{ return a.house < b.house;
}

pirate P[2][1000];
long long MinSpace[1001][1001]; // MinSpace[k][i] = Minimum amount of space needed to make i of the first k pirates happy

int main()
{ int runs, run, n, i, k, xc, lc, x, l, t, happy;
  int N[2];
  pirate p;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d\n%d %d\n", &n, &xc, &lc);
    N[0] = N[1] = 0; // Number of houses on each side of the captain
    for (i = 1; i < n; i++)
    { scanf("%d %d\n", &x, &l);
      t = (x > xc ? 0 : 1); // 0 or 1 depending on whether the pirate's house is to the left or right of the captain's
      p.house = 2ll*abs(x-xc); // Absolute MinSpacetance relative to the captain's house
      p.shiplength = 2*l; // Everything is multiplied with 2 to avoid half-integers
      P[t][N[t]++] = p;
    }
    happy = 1; // The captain is happy
    for (t = 0; t < 2; t++) // For both directions
    { sort(P[t], P[t] + N[t]); // Sort the pirates by distance
      memset(MinSpace, 127, sizeof(MinSpace)); // Initialize MinSpace to "infinity"
      MinSpace[0][0] = lc;
      for (k = 1; k <= N[t]; k++)
      { p = P[t][k-1];
        MinSpace[k][0] = lc; // No happy pirates: only the captain's ship is present
        for (i = 1; i <= k; i++)
        { // Determine minimum amount of space needed to make i of the first k pirates happy using DP
          if (MinSpace[k-1][i-1] <= p.house) // Pirate p's ship can be placed; check if it's an improvement over MinSpace[k-1][i]
            MinSpace[k][i] = min(MinSpace[k-1][i], max(p.house, MinSpace[k-1][i-1] + p.shiplength));
          else // Pirate p's ship can't be placed; copy previous solution
            MinSpace[k][i] = MinSpace[k-1][i];
        }
      }
      for (i = N[t]; MinSpace[N[t]][i] > alot; i--); // Look for highest number of satisfiable pirates
      happy += i;
    }
    printf("%d\n", happy);
  }
  return 0;
}
