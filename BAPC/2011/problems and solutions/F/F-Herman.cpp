#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
#include <algorithm>
using std::sort;
using std::max;
#include <vector>
using std::vector;

#define INT long double

struct Solution
{
  int Nbounce;
  int Ebounce;
  int Sbounce;
  int Wbounce;
  Solution(int n = 0, int e = 0, int s = 0, int w = 0):
    Nbounce(n), Ebounce(e), Sbounce(s), Wbounce(w) {};
  bool operator<(const Solution& s) const
  {
    if (Nbounce < s.Nbounce) return true;
    if (Nbounce > s.Nbounce) return false;
    if (Ebounce < s.Ebounce) return true;
    if (Ebounce > s.Ebounce) return false;
    if (Sbounce < s.Sbounce) return true;
    if (Sbounce > s.Sbounce) return false;
    if (Wbounce < s.Wbounce) return true;
    return false;
  }
};

ostream& operator<<(ostream& o, const Solution& s)
{
  return o << s.Nbounce << ' ' << s.Ebounce << ' ' << s.Sbounce << ' ' << s.Wbounce;
}

#define TEST(XDIR,YDIR)\
    for (int col = 0; col <= bounces; ++col)\
    {\
      int row = bounces - col;\
      INT destx = XDIR * col * sizex + ((col & 1) == 0 ? foex : sizex - foex);\
      INT desty = YDIR * row * sizey + ((row & 1) == 0 ? foey : sizey - foey);\
      INT sqDist = (destx - saitox) * (destx - saitox) + (desty - saitoy) * (desty - saitoy);\
      if (sqDist > bestSqDist) continue;\
      if (sqDist < bestSqDist)\
      {\
        bestSqDist = sqDist;\
        solutions.clear();\
      }\
      if (sqDist == bestSqDist)\
        solutions.push_back(Solution((row+(1+YDIR)/2)/2, (col+(1+XDIR)/2)/2, (row+(1-YDIR)/2)/2, (col+(1-XDIR)/2)/2));\
    }


int main()
{
  INT nrTests = 0;
  cin >> nrTests;
  while (nrTests-- > 0)
  {
    INT sizex = 0;
    INT sizey = 0;
    int bounces = 0;
    INT saitox = 0;
    INT saitoy = 0;
    INT foex = 0;
    INT foey = 0;
    cin >> sizex >> sizey >> bounces >> saitox >> saitoy >> foex >> foey;

    // initialize an upper bound that is guaranteed to be strictly more than in any valid solution
    INT bestSqDist = (bounces + 1) * (sizex + sizey); bestSqDist *= bestSqDist;
    vector<Solution> solutions;
    solutions.clear();
    TEST( 1, 1); // test NE quadrant
    TEST( 1,-1); // test SE quadrant
    TEST(-1, 1); // test NW quadrant
    TEST(-1,-1); // test SW quadrant

    if (!solutions.empty())
    {
      sort(solutions.begin(), solutions.end());
      vector<Solution>::const_iterator j = solutions.begin();
      cout << *j << endl;
      for (vector<Solution>::const_iterator i = solutions.begin(); i != solutions.end(); ++i)
      {
        // ignore doubles
        if (*j < *i) cout << *i << endl;
        j = i;
      }    
    }
    cout << '0' << endl;
  }
}
