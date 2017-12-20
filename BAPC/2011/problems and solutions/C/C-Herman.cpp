#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;
using std::endl;
#include <algorithm>
using std::min;
using std::max;
#include <vector>
using std::vector;
#include <stdio.h>

// EXACT is defined if this file is included from another, together with an exact arithmetic implementation
// If not, just use long doubles:
#ifndef EXACT
typedef long double BigNumber;
int sign(BigNumber n) { return (n > 0 ? 1 : (n < 0 ? -1 : 0)); }
#endif

struct Point
{
  int x;
  int y;
  Point(unsigned int xx = 0, unsigned int yy = 0): x(xx), y(yy) {};
};

const int ABOVE = 1;
const int BELOW = -1;

struct Line
{
  // line ax + by + c = 0
  const BigNumber a;
  const BigNumber b;
  const BigNumber c;
  Line(const Point& p1, const Point& p2):
    a(p1.y - p2.y),
    b(p2.x - p1.x),
    c(BigNumber(p1.x) * BigNumber(p2.y) - BigNumber(p1.y) * BigNumber(p2.x))
  {};
  bool is(const int aboveOrBelow, const Point& p) const
  {
    if (sign(b) == 0) return false;
    return (sign(a * p.x + b * p.y + c) == -aboveOrBelow * sign(b));
  }
};

struct Intersection
{
  const BigNumber Dab;
  const BigNumber Dbc;
  const BigNumber Dca;
  Intersection(const Line* l, const Line* m): 
    Dab(l->a * m->b - l->b * m->a), // note: should be non-zero, otherwise lines are parallel
    Dbc(l->b * m->c - l->c * m->b),
    Dca(l->c * m->a - l->a * m->c)
  {};
  bool is(const int aboveOrBelow, const Line* l) const
  {
    if (sign(l->b) == 0) return false;
    return (sign(l->a * Dbc + l->b * Dca + l->c * Dab) == aboveOrBelow * sign(l->b) * sign(Dab));
  }
  bool isRightOf(const int x) const
  {
    return (sign(Dab * x - Dbc) == -sign(Dab));
  }
};

struct Envelope
{
  vector<Line*> edges;
  vector<Intersection*> vertices;
  const int aboveOrBelow;
  Envelope(int r, int x1, int y1, int x3, int y3):
    aboveOrBelow(r)
  {
    Line* l1 = new Line(Point(x1,y1), Point(x1,y3)); edges.push_back(l1);
    Line* l2 = new Line(Point(x1,y3), Point(x3,y3)); edges.push_back(l2);
    Line* l3 = new Line(Point(x3,y3), Point(x3,y1)); edges.push_back(l3);
    Intersection* p1 = new Intersection(l1, l2); vertices.push_back(p1);
    Intersection* p2 = new Intersection(l2, l3); vertices.push_back(p2);
  }
  void insert(Line* l)
  {
    int i = 0;                   // to hold the first vertex cut off by the new line
    while (i < vertices.size() && vertices[i]->is(-aboveOrBelow, l)) ++i;
    if (i == vertices.size()) 
    {
      // line lies completely outside envelope
      delete l;
      return;
    }
    int j = vertices.size() - 1; // to hold the last vertex cut off by the new line
    while (vertices[j]->is(-aboveOrBelow, l)) --j;
    Intersection* p1 = new Intersection(edges[i], l);
    Intersection* p2 = new Intersection(l, edges[j+1]);
    // delete edges i+1 t/m j
    for (int k = i+1; k <= j; ++k) delete edges[k];
    edges.erase(edges.begin() + i+1, edges.begin() + j+1);
    // delete intersections i t/m j
    for (int k = i; k <= j; ++k) delete vertices[k];
    vertices.erase(vertices.begin() + i, vertices.begin() + j+1);
    // insert new edge
    edges.insert(edges.begin() + i+1, l);
    // insert new vertices
    vertices.insert(vertices.begin() + i, p1);
    vertices.insert(vertices.begin() + i+1, p2);
  }
  bool contains(Point& p)
  {
    // find edge of hull above/below point
    int left = 0;                 // leftmost candidate edge
    int right = edges.size() - 1; // rightmost candidate edge
    while (right > left)
    {
      int mid = (left + right - 1) / 2;
      if (vertices[mid]->isRightOf(p.x))
        right = mid;
      else
        left = mid+1;
    }
    return (edges[left]->is(aboveOrBelow, p));
  }
  ~Envelope()
  {
    for (vector<Line*>::iterator i = edges.begin(); i != edges.end(); ++i) delete *i;
    for (vector<Intersection*>::iterator i = vertices.begin(); i != vertices.end(); ++i) delete *i;
  }
};

int main()
{
  int nrArchipelagos;
  for (scanf("%d", &nrArchipelagos); nrArchipelagos > 0; --nrArchipelagos)
  {
    vector<Point> islands;
    int nrIslands;
    int minx = (1 << 30); int maxx = 0; 
    int miny = (1 << 30); int maxy = 0;
    for (scanf("%d", &nrIslands); nrIslands > 0; --nrIslands)
    {
      Point p; scanf("%d", &p.x); scanf("%d", &p.y);
      islands.push_back(p);
      minx = min(minx, p.x);
      maxx = max(maxx, p.x);
      miny = min(miny, p.y);
      maxy = max(maxy, p.y);
    }
    nrIslands = islands.size();
    int nrCases; 
    for (scanf("%d", &nrCases); nrCases > 0; --nrCases)
    {
      Envelope upperHull(ABOVE, minx-1, miny-1, maxx+1, maxy+1);
      Envelope lowerHull(BELOW, minx-1, maxy+1, maxx+1, miny-1);
      int nrViews;
      for (scanf("%d", &nrViews); nrViews > 0; --nrViews)
      {
        int p1; int p2;
        scanf("%d", &p1); scanf("%d", &p2);
        --p1; --p2; // numbering from 0 instead of from 1
        Line* l = new Line(islands[p1], islands[p2]);
        if (islands[p1].x < islands[p2].x)
          upperHull.insert(l);
        else
          lowerHull.insert(l);
      }
      for (int i = 0; i < islands.size(); ++i)
        if (upperHull.contains(islands[i]) && lowerHull.contains(islands[i])) 
          cout << i + 1 << endl;
      cout << '0' << endl;
    } 
  }
}

