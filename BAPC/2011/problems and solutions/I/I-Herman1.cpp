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
      if (pirates[side].size() > 0)
      {
        // sort by decreasing distance from captain
        sort(pirates[side].begin(), pirates[side].end()); 
        // make the outermost pirate happy
        ++happyPirates;
        // maintain the distance from the captain that is maintained by ships placed so far
        unsigned int distance = pirates[side][0].dx;
        // maintain the distance from the captain that could be maintained if placing one more pirate
        unsigned int nextDistance = 0;
        // try to make more pirates happy            
        for (int i = 1; i < pirates[side].size(); ++i)
        {
          // check if one of the pirates previously seen can now be placed
          if (pirates[side][i].dx <= nextDistance)
          {
            ++happyPirates;
            distance = nextDistance;
            nextDistance = 0;
          }
          // update nextDistance to reflect the possibility of placing pirate i
          if (distance >= captainL + pirates[side][i].dl)
            nextDistance = max(nextDistance, min(distance - pirates[side][i].dl, pirates[side][i].dx));
        }
        // check if one of the pirates previously seen can now be placed
        if (nextDistance >= captainL) ++happyPirates;
      }
    }
    cout << happyPirates << endl;
  }
}
