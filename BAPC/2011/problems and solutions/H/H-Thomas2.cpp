// Walking the Plank
// Solution in O(NP) by Thomas Beuman

#include <cstdio>
#include <algorithm>
using namespace std;

int Duration[1000][4]; // The time each pirate takes for every step
int ETA[1000]; // Expected time of arrival at the plank
int Slowness[1000]; // The time each pirate takes to do his business on their side of the ship
bool OnPirateShip[1000]; // Whether or not each pirate is on the pirate ship

int main()
{ int runs, run, N, P, p, i, p1, p2, q, c;
  int time;
  scanf("%d", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d", &N, &P);
    for (p = 0; p < P; p++)
      for (i = 0; i < 4; i++)
        scanf("%d", &Duration[p][i]);
    time = 0;
    for (p = 0; p < P; p++)
    { ETA[p] = 0;
      Slowness[p] = -p; // For the purpose of ordening the pirates correctly at the start
      OnPirateShip[p] = true;
    }
    c = 0; // Number of pirates on the commercial ship
    while (N > 0 || c > 0) // While there are items left to get or there are pirates on the commercial ship
    { p1 = p2 = -1; // The first pirate to leave the commercial ship and the pirate ship respectively
      for (p = 0; p < P; p++)
      { q = (OnPirateShip[p] ? p2 : p1);
        if (q == -1 || ETA[p] < ETA[q] || (ETA[p] == ETA[q] && Slowness[p] > Slowness[q]))
        { if (OnPirateShip[p])
            p2 = p;
          else
            p1 = p;
        }
      }
      if (N == 0) // No items left to get
        p2 = -1;
      if ((p1 < 0 || ETA[p1] > time) && (p2 < 0 || ETA[p2] > time)) // If neither pirate is ready to cross at this time
      { // Update time
        if (p1 < 0)
          time = ETA[p2];
        else if (p2 < 0)
          time = ETA[p1];
        else
          time = min(ETA[p1], ETA[p2]);
      }
      if (p1 >= 0 && ETA[p1] <= time) // The pirate on the commercial ship crosses over
      { time += Duration[p1][2];
        ETA[p1] = time + Duration[p1][3];
        Slowness[p1] = Duration[p1][3];
        OnPirateShip[p1] = true;
        c--;
      }
      else // The pirate on the pirate ship crosses over
      { time += Duration[p2][0];
        ETA[p2] = time + Duration[p2][1];
        Slowness[p2] = Duration[p2][1];
        OnPirateShip[p2] = false;
        c++;
        N--; // One less item left to get
      }
    }
    printf("%d\n", time);
  }
  return 0;
}

