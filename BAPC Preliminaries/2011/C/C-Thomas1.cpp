// Attack of the Giant n-pus
// Solution by Thomas Beuman

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int PirateX[101], PirateY[101], PirateV[101];  // Pirate locations and speed
int TentacleX[101], TentacleY[101];            // Tentacle locations
double Time[101][101], ListOfTimes[10000];

bool Seen[101];
int Match[101];

// Looks for a (new) match for pirate i using DFS
bool bpmmatch (int i, int n, double timelimit)
{ int j;
  for (j = 1; j <= n; j++)
    if (Time[i][j] <= timelimit && !Seen[j])
    { Seen[j] = true;
      if (Match[j] < 0 || bpmmatch(Match[j], n, timelimit))
      { Match[j] = i;
        return true;
      }
    }
  return false;
}

int maxbipartitematching (int p, int n, double timelimit)
{ memset(Match, -1, (n+1)*sizeof(int));
  int count = 0, i;
  for (i = 1; i <= p; i++)
  { memset(Seen, false, (n+1)*sizeof(bool));
    if (bpmmatch(i, n, timelimit))
      count++;
  }
  return count;
}

int main()
{ int runs, run, n, p, i, j, t, lowerbound, upperbound, middle;
  double timelimit;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &n, &p);
    for (i = 0; i <= p; i++)
      scanf("%d %d %d\n", &PirateX[i], &PirateY[i], &PirateV[i]);
    for (j = 0; j <= n; j++)
      scanf("%d %d\n", &TentacleX[j], &TentacleY[j]);
    // Calculate all times
    t = 0;
    for (i = 1; i <= p; i++)
      for (j = 1; j <= n; j++)
      { Time[i][j] = sqrt((PirateX[i]-TentacleX[j])*(PirateX[i]-TentacleX[j]) +
                          (PirateY[i]-TentacleY[j])*(PirateY[i]-TentacleY[j])) / PirateV[i];
        ListOfTimes[t++] = Time[i][j];
      }
    Time[0][0] = sqrt((PirateX[0]-TentacleX[0])*(PirateX[0]-TentacleX[0]) +
                      (PirateY[0]-TentacleY[0])*(PirateY[0]-TentacleY[0])) / PirateV[0];
    sort(ListOfTimes, ListOfTimes + p*n);
    // Binary search on the time within all tentacles are reached 
    lowerbound = -1;
    upperbound = p*n-1; // Lowerbound is too low, upperbound could be it
    while (upperbound - lowerbound > 1)
    { middle = (lowerbound + upperbound) / 2;
      timelimit = ListOfTimes[middle];
      if (maxbipartitematching(p, n, timelimit) == n) // All tentacles can be matched within this timelimit
        upperbound = middle;
      else
        lowerbound = middle;
    }
    printf("%.9lf\n", ListOfTimes[upperbound] + Time[0][0]);
  }
  return 0;
}
