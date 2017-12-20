#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <stdlib.h>


typedef long double BigNumber;

struct Island
{
  int x;
  int y;
  Island(): x(0), y(0) {};
};

struct View
{
  BigNumber a;
  BigNumber b;
  BigNumber c;
  View(): a(0), b(0), c(0) {};
  void setIslands(Island& i1, Island& i2)
  {
    a = i2.y - i1.y;
    b = i1.x - i2.x;
    c = BigNumber(i1.x) * BigNumber(i2.y) - BigNumber(i1.y) * BigNumber(i2.x);
  }
  bool notVisibleFrom(Island& i)
  {
    return (a * i.x + b * i.y <= c);
  }
};

int main()
{
  int nrArchipelagos;
  for (cin >> nrArchipelagos; nrArchipelagos > 0; --nrArchipelagos)
  {
    int nrIslands; cin >> nrIslands;
    Island* islands = (Island*) malloc (nrIslands * sizeof(Island));
    for (int i = 0; i < nrIslands; ++i) cin >> islands[i].x >> islands[i].y;
    int nrCases; 
    for (cin >> nrCases; nrCases > 0; --nrCases)
    {
      int nrViews; cin >> nrViews;
      View* views = (View*) malloc (nrViews * sizeof(View));
      for (int v = 0; v < nrViews; ++v)
      {
        int i1; int i2; cin >> i1 >> i2; --i1; --i2; // numbering from 0 instead of from 1
        views[v].setIslands(islands[i1], islands[i2]);
      }
      for (int i = 0; i < nrIslands; ++i)
      {
        int v = 0;
        while(true)
        {
          if (views[v].notVisibleFrom(islands[i])) break;
          if (++v < nrViews) continue;
          cout << i + 1 << endl;
          break;
        }
      }
      cout << 0 << endl;
    } 
  }
}

