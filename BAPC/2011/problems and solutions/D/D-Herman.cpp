#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <algorithm>
using std::min;

const int IMPOSSIBLE = 101;

int main()
{
  int lit[100];
  int nrCases;
  for (cin >> nrCases; nrCases > 0; --nrCases)
  {
    int nrLights; cin >> nrLights;
    int D; cin >> D; if (D > nrLights-1) D = nrLights-1;
    unsigned int fullMask = ((2 << D) << D); --fullMask; // bitmap with 2D+1 bits
    for (int i = 0; i < nrLights; ++i) cin >> lit[i];
    int bestSolution = IMPOSSIBLE;
    unsigned int initSwitches = 0;   // bitmap: which from the 1st D switches are flipped
    unsigned int initNrSwitches = 0; // how many from the 1st D switches are flipped
    unsigned int initMask = 0;       // bitmap: how the 1st 2D lights change as a result
    for (unsigned int i = 0; i < (1 << D); ++i)
    {
      int switched = initNrSwitches; // how many switches we are currently flipping
      unsigned int mask = initMask;  // how the next 2D lights change as a result
      // find out what still needs to be switched
      for (int l = 0; l < nrLights - D; ++l)
      {
        if (lit[l] != (mask & 1))
        {
          // flip switch l+D
          ++switched;
          mask ^= fullMask;
        }
        mask >>= 1;
      }
      // find out if the last lights are now off
      bool off = true;
      for (int l = nrLights - D; l < nrLights; ++l)
      {
        if (lit[l] != (mask & 1))
        {
          off = false;
          break;
        }
        mask >>= 1;
      }
      if (off) bestSolution = min(bestSolution, switched);
      
      // prepare for next solution:
      // find the bit that increases from i to i+1
      unsigned int changeSwitch = ((i+1) & ~i);
      // find out how the solution changes: 
      // is a switch that was previously left alone now flipped, or
      // is a switch that was previously flipped now left alone?
      if ((initSwitches & changeSwitch) == 0)
        ++initNrSwitches;
      else
        --initNrSwitches;
      initSwitches ^= changeSwitch;
      initMask ^= ((changeSwitch * (2 << D)) - 1);
    }
    if (bestSolution == IMPOSSIBLE)
      cout << "impossible" << endl;
    else
      cout << bestSolution << endl;
  }
}
