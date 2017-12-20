#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <algorithm>
using std::min;
using std::max;
using std::sort;
#include <vector>
using std::vector;
#include <math.h>

struct Pirate
{
  unsigned int dx;
  unsigned int dl;
  Pirate(): dx(0), dl(0) {};
  Pirate& operator=(const Pirate& p) { dx = p.dx; dl = p.dl; return *this; }
  bool operator<(const Pirate& p) const { return (dx > p.dx); }
};

void readPirate(Pirate& p, const int captainX, int& side)
{
  int x;
  cin >> x >> p.dl;
  x -= captainX;
  side = (x < 0 ? 0 : 1);
  if (x < 0) x = -x;
  p.dx = x;
  p.dx *= 2;
  p.dl *= 2;
}

int main()
{
  unsigned int* maxDistanceFromCaptain[1000];
  for (int i = 0; i <= 999; ++i)
    maxDistanceFromCaptain[i] = (unsigned int*) malloc ((i+2) * sizeof(unsigned int));
  // semantics of entry [i][j]: 2 * max dist we can keep from captain's 
  // home while making j out of the farthest i pirates happy
  int nrCases;
  for (cin >> nrCases; nrCases > 0; --nrCases)
  {
    int totalPirates; cin >> totalPirates;
    vector<Pirate> pirates[2];
    int captainX; int captainL;
    cin >> captainX >> captainL;
    for (int i = 1; i < totalPirates; ++i)
    {
      Pirate p; int side;
      readPirate(p, captainX, side);
      if (p.dx >= captainL) pirates[side].push_back(p);
    }
    int happyPirates = 1; // captain always happy
    for (int side = 0; side < 2; ++side)
    {
      // sort by decreasing distance from captain
      sort(pirates[side].begin(), pirates[side].end()); 
      for (int farthestPirates = 0; farthestPirates <= pirates[side].size(); ++farthestPirates)
      {
        maxDistanceFromCaptain[farthestPirates][0] = 0xFFFFFFFF;        // not posing any constraints
        maxDistanceFromCaptain[farthestPirates][farthestPirates+1] = 0; // impossible
        for (int madeHappy = 1; madeHappy <= farthestPirates; ++madeHappy)
        {
          // solution without making the closest pirate happy:
          maxDistanceFromCaptain[farthestPirates][madeHappy] = maxDistanceFromCaptain[farthestPirates-1][madeHappy];
          // if possible, consider the solution that makes the closest pirate happy:
          if (maxDistanceFromCaptain[farthestPirates-1][madeHappy-1] == 0xFFFFFFFF)
            maxDistanceFromCaptain[farthestPirates][madeHappy] = pirates[side][farthestPirates-1].dx;
          else if (
               maxDistanceFromCaptain[farthestPirates-1][madeHappy-1] >= max(
                 pirates[side][farthestPirates-1].dx,
                 captainL + pirates[side][farthestPirates-1].dl
               )
             )
            maxDistanceFromCaptain[farthestPirates][madeHappy] = max(
              maxDistanceFromCaptain[farthestPirates][madeHappy],
              min(
                pirates[side][farthestPirates-1].dx,
                maxDistanceFromCaptain[farthestPirates-1][madeHappy-1] - pirates[side][farthestPirates-1].dl
              )
            );
        }
      }
      int madeHappy = pirates[side].size();
      while (madeHappy > 0 && maxDistanceFromCaptain[pirates[side].size()][madeHappy] < captainL) --madeHappy;
      happyPirates += madeHappy;
    }
    cout << happyPirates << endl;
  }
}
