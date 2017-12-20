// Parking Ships
// Solution in O(N log N) by Thomas Beuman

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const long long INF = 10000000000ll; // "Infinity"

struct pirate
{ long long house, shiplength;
};

bool operator < (const pirate& a, const pirate& b)
{ return a.house < b.house;
}

pirate P[2][1000];

int main()
{ int runs, run, n, i, xc, lc, x, l, t, happy;
  int N[2];
  long long lastship, minspace;
  pirate p;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d\n%d %d\n", &n, &xc, &lc);
    N[0] = N[1] = 0; // Number of houses on each side of the captain
    for (i = 1; i < n; i++)
    { scanf("%d %d\n", &x, &l);
      t = (x > xc ? 0 : 1); // 0 or 1 depending on whether the pirate's house is to the left or right of the captain's
      p.house = 2ll*abs(x-xc); // Absolute distance relative to the captain's house
      p.shiplength = 2*l; // Everything is multiplied with 2 to avoid half-integers
      if (p.house >= lc) // No need to include this pirate if the captain's ship is in front of this pirate's house
        P[t][N[t]++] = p;
    }
    happy = 1; // The captain is happy
    for (t = 0; t < 2; t++) // For both directions
    { sort(P[t], P[t] + N[t]); // Sort the pirates by distance
      lastship = lc; // The end of the last ship (is initially the captain's ship)
      for (i = 0; i < N[t]; happy++)
      { minspace = INF;
        // Look for ship that requires least amount of space
        // (No need to reset i as it is the index of the first house after lastship)
        for (; i < N[t] && P[t][i].house < minspace; i++)
          minspace = min(minspace, max(P[t][i].house, lastship + P[t][i].shiplength));
        lastship = minspace;
      }
    }
    printf("%d\n", happy);
  }
  return 0;
}
