// Ultimate Finishing Strike
// Solutions by Thomas Beuman

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct path
{ int Bounces[4];
  path() {}
  path (int n, int e, int s, int w)
  { Bounces[0] = n;  Bounces[1] = e;  Bounces[2] = s;  Bounces[3] = w;
  }
};

// For sorting the paths
bool operator < (const path& s1, const path& s2)
{ int i;
  for (i = 0; i < 4 && s1.Bounces[i] == s2.Bounces[i]; i++);
  return i < 4 && s1.Bounces[i] < s2.Bounces[i];
}

vector<path> Solutions; // All shortest paths

// Returns path length (squared) given number of east&west bounces (ew) and north&south bounces (ns)
long long dissq (int L, int W, int xs, int ys, int xf, int yf, int ew, int ns)
{ long long x = ew*L + (ew%2 ? L-xf : xf), y = ns*W + (ns%2 ? W-yf : yf); // Virtual location of foe
  return (x-xs)*(x-xs) + (y-ys)*(y-ys);
}

int main()
{ int runs, run, L, W, B, xs, ys, xf, yf, i, j, k;
  long long d, mindissq;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d\n%d %d\n%d %d\n", &L, &W, &B, &xs, &ys, &xf, &yf);
    mindissq = 1ll << 60; // Minimum path length (squared)
    for (i = -B; i <= B; i++) // Number of bounces on east and west wall (negative = west first)
      for (k = -1; k <= 1; k += 2)
      { j = k*(B-abs(i)); // Number of bounces on north and south wall (negative = south first)
        d = dissq(L, W, xs, ys, xf, yf, i, j);
        if (d < mindissq)
        { mindissq = d;
          Solutions.clear();
        }
        if (d == mindissq) // Add path to solutions
        { int n = (j > 0 ? j+1 : -j) / 2, e = (i > 0 ? i+1 : -i) / 2; // Number of bounces on north and east wall resp.
          Solutions.push_back(path(n, e, abs(j)-n, abs(i)-e));
        }
        if (j == 0)
          break;
      }
    // Sort and output
    sort(Solutions.begin(), Solutions.end());
    for (i = 0; i < Solutions.size(); i++)
      for (j = 0; j < 4; j++)
        printf("%d%c", Solutions[i].Bounces[j], j < 3 ? ' ' : '\n');
    printf("0\n");
  }
  return 0;
}
