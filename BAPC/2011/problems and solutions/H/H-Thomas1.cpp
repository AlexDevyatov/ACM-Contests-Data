// Walking the Plank
// Solution in O(N log P) by Thomas Beuman

#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int Duration[1000][4]; // The time each pirate takes for every step
int ETA[1000]; // Expected time of arrival at the plank
int Slowness[1000]; // The time each pirate takes to do his business on their side of the ship

// Compare operator: true if p1 is behind p2 in the queue (hence p1 has less priority)
struct cmp
{ bool operator() (const int& p1, const int& p2)
  { return ETA[p1] > ETA[p2] || (ETA[p1] == ETA[p2] && Slowness[p1] < Slowness[p2]);
  }
};

typedef priority_queue<int, vector<int>, cmp>  PQ;

int main()
{ int runs, run, N, P, p, i, p1, p2;
  int time;
  PQ pirateship, commship;
  scanf("%d", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d", &N, &P);
    for (p = 0; p < P; p++)
      for (i = 0; i < 4; i++)
        scanf("%d", &Duration[p][i]);
    time = 0;
    pirateship = PQ();
    commship = PQ();
    for (p = 0; p < P; p++)
    { ETA[p] = 0;
      Slowness[p] = -p; // For the purpose of ordening the pirates correctly at the start
      pirateship.push(p);
    }
    while (N > 0 || !commship.empty()) // While there are items left to get or there are pirates on the commercial ship
    { p1 = (commship.empty() ? -1 : commship.top()); // The first pirate to leave the commercial ship
      p2 = (N == 0 || pirateship.empty() ? -1 : pirateship.top()); // The first pirate to leave the pirate ship
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
      { commship.pop();
        time += Duration[p1][2];
        ETA[p1] = time + Duration[p1][3];
        Slowness[p1] = Duration[p1][3];
        pirateship.push(p1);
      }
      else // The pirate on the pirate ship crosses over
      { pirateship.pop();
        time += Duration[p2][0];
        ETA[p2] = time + Duration[p2][1];
        Slowness[p2] = Duration[p2][1];
        commship.push(p2);
        N--; // One less item left to get
      }
    }
    printf("%d\n", time);
  }
  return 0;
}

