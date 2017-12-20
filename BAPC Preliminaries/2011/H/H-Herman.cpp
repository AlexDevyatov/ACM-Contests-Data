#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::hex;
using std::setw;
#include <stack>
using std::stack;
#include <cstdlib>

/*
void showGrid(bool G[], int COL, int ROW, int ALL)
{
  for (int i = ALL-ROW; i >= 0; i -= ROW)
  {
    for (int j = 0; j < ROW; j += COL)
    {
      int K = 0;
      for (int T = 0; T < 8; T += 2)
      {
        int k = (G[i+j+T] ? 1 : 0);
        if (G[i+j+T+1] != k) cout << "!?";
        K <<= 1; K += k;
      }
      cout << hex << setw(1) << K;
    }
    cout << endl;
  }  
}
*/

int main()
{
  int nrTests; cin >> nrTests;
  for (int test = 1; test <= nrTests; ++test)
  {
    int n; int k; cin >> n >> k;
    if (n < 1) cerr << "Hall too small" << endl;
    // make a grid of size $2n+1$ rows times $2n+1$ columns times 8 time steps
    int N = 2*n + 1;
    int COL = 8;
    int ROW = N * COL;
    int ALL = N * ROW;
    bool* G = (bool*) malloc (ALL * sizeof(bool));
    // make whole grid inaccessible
    for (int i = 0; i < ALL; ++i) G[i] = false;
    // draw left-to-right corridors
    for (int i = ROW; i < ALL; i += 2*ROW)
      for (int j = COL; j < ROW-COL; j += COL)
        for (int t = 0; t < 8; ++t)
          G[i+j+t] = true;
    // draw front-to-back corridors
    for (int i = COL; i < ROW; i += 2*COL)
      for (int j = 0; j < ALL; j += ROW)
        for (int t = 0; t < 8; ++t)
          G[i+j+t] = true;
    // put in the guards
    for (int g = 1; g <= k; ++g)
    {
      int grow; int gcol; char gchar; int gphase;
      cin >> grow >> gcol >> gchar;
      if (grow < 1 || gcol < 1 || gcol > 2*n-1 || gcol > 2*n-1) cerr << "Guard not place inside hall" << endl;
      if ((grow & 1) == 0 || (gcol & 1) == 0) cerr << "Guard not placed at intersection of corridors" << endl;
      switch (gchar)
      {
        case 'L': gphase = 0; break;
        case 'B': gphase = 1; break;
        case 'R': gphase = 2; break;
        case 'F': gphase = 3; break;
        default: cerr << "Guard appears to be sleeping" << endl;
      }
      // looking left
      for (int j = gcol; j > 0; --j)
        for (int t = 0; t < 2; ++t)
          G[grow*ROW + j*COL + t + 2*((4-gphase)%4)] = false;
      // looking to back
      for (int i = grow; i < N-1; ++i)
        for (int t = 0; t < 2; ++t)
          G[i*ROW + gcol*COL + t + 2*((5-gphase)%4)] = false;
      // looking right
      for (int j = gcol; j < N-1; ++j)
        for (int t = 0; t < 2; ++t)
          G[grow*ROW + j*COL + t + 2*((6-gphase)%4)] = false;
      // looking to front 
      for (int i = grow; i > 0; --i)
        for (int t = 0; t < 2; ++t)
          G[i*ROW + gcol*COL + t + 2*((7-gphase)%4)] = false;
    }
    
    stack<int> reachable;
    // put in all the entrances
    for (int i = COL; i < ROW; i+= 2*COL) 
      for (int t = 0; t < 8; ++t)
        reachable.push(i+t);
    // search
    bool succeeds = false;
    while (!reachable.empty())
    {
      int i = reachable.top();
      reachable.pop();
      if (!G[i]) continue; // blocked, not safe, or already visited
      G[i] = false; // do not come back here
      if (i >= ALL - ROW) 
      { 
        succeeds = true;
        break;
      }
      int dt = 1; if (i % 8 == 7) dt = -7;
      // try going forward; only if that position is both:
      // - currently safe, so that it is safe to start moving;
      // - not visited before at the current time (mod 16) (in which 
      //   case visiting it at current time + 2 (mod 16) must have been
      //   added to the queue already)
      if (G[i + ROW]) reachable.push(i + dt + ROW); 
 
      reachable.push(i + dt); // just wait here
      
      if (G[i - COL]) reachable.push(i + dt - COL); // go left
      if (G[i + COL]) reachable.push(i + dt + COL); // go right
      if (i > ROW && G[i - ROW]) reachable.push(i + dt - ROW); // go to front
    }
    if (succeeds) cout << "succeeds" << endl; else cout << "fails" << endl;
    delete G;
  }   
}

