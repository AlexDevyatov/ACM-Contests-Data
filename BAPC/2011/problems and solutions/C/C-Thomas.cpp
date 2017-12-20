// Find the Treasure
// Solution by Thomas Beuman

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-7; // For comparing doubles

struct point
{ double x, y;
};

struct line
{ int x1, y1, x2, y2;
  double angle;
};

bool line_cmp (const line& v1, const line& v2)
{ return fabs(v1.angle) < fabs(v2.angle);
}

int X[500000], Y[500000];
line View[10000];
line Edge[2][10000]; // Left and right borders between which the treasure island must be
point Vertex[2][10000]; // Intersection points between edges

// Calculates the intersection point of two lines; returns false if the lines are parallel
bool intersection (line s1, line s2, point& p)
{ long long xa = s1.x1, ya = s1.y1, xb = s1.x2, yb = s1.y2;
  long long xc = s2.x1, yc = s2.y1, xd = s2.x2, yd = s2.y2;
  long long d = (xa-xb)*(yc-yd) - (xc-xd)*(ya-yb);
  if (d == 0) return false; // Lines are parallel
  p.x = -((xa-xb)*((double)xc*yd-(double)xd*yc) - (xc-xd)*((double)xa*yb-(double)xb*ya)) / d;
  p.y = ((ya-yb)*((double)yc*xd-(double)yd*xc) - (yc-yd)*((double)ya*xb-(double)yb*xa)) / d;
  return true;
}

// (Doubled) area of a triangle; is negative if the vertices are in clockwise order
double area (double x1, double y1, double x2, double y2, double x3, double y3)
{ return x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y1 - x1*y3;
}

// Returns if p is on the wrong side of view v
bool outofbounds (const point& p, const line& v)
{ return area(p.x, p.y, (double)v.x1, (double)v.y1, (double)v.x2, (double)v.y2) > 0;
}

// (Doubled) area of a triangle; is negative if the vertices are in clockwise order
long long area (long long x1, long long y1, long long x2, long long y2, long long x3, long long y3)
{ return x1*y2 - x2*y1 + x2*y3 - x3*y2 + x3*y1 - x1*y3;
}

// Returns if (x,y) is on the wrong side of view v
bool outofbounds (int x, int y, const line& v)
{ return area((long long)x, (long long)y, (long long)v.x1, (long long)v.y1, (long long)v.x2, (long long)v.y2) >= 0;
}

int main()
{ int runs, run, cases, casenr, n, m, i, j, k, t, u, v, w;
  int N[2];
  line s;
  point p;
  bool withinbounds[2];
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d\n", &n);
    for (i = 0; i < n; i++)
      scanf("%d %d\n", &X[i], &Y[i]);
    scanf("%d\n", &cases);
    for (casenr = 0; casenr < cases; casenr++)
    { scanf("%d\n", &m);
      for (k = 0; k < m; k++)
      { scanf("%d %d\n", &i, &j);
        i--; j--;
        s.x1 = X[i]; s.y1 = Y[i];
        s.x2 = X[j]; s.y2 = Y[j];
        s.angle = atan2(Y[i]-Y[j], X[i]-X[j]);
        View[k] = s;
      }
      sort(View, View + m, line_cmp); // Sort all views by angle
      N[0] = N[1] = 0; // Number of edges in left (=0) and right (=1) border
      for (i = 0; i < m; i++)
      { t = (View[i].angle < 0 ? 0 : 1); // Border which this view belongs to
        if (N[t] == 0) // No edges yet
        { Edge[t][N[t]++] = View[i];
          continue;
        }
        // Delete vertices/edges which are out of bounds
        while (N[t] > 1 && outofbounds(Vertex[t][N[t]-2], View[i]))
          N[t]--;
        // Add this view as edge and compute intersection with border
        if (intersection(Edge[t][N[t]-1], View[i], p))
        { Vertex[t][N[t]-1] = p;
          Edge[t][N[t]++] = View[i];
        }
        // Special case: just one edge in border which is parellel to new edge
        // Replace the old view if the new view is stricter
        else if (N[t] == 1 && outofbounds(Edge[t][0].x1, Edge[t][0].y1, View[i]))
          Edge[t][0] = View[i];
      }
      for (i = 0; i < n; i++) // Check all islands
      { for (t = 0; t < 2; t++) // For both borders
        { u = 0;
          w = N[t]-1;
          // Binary search to find the edge located at the y-coordinate of this island
          // (The vertices are sorted by y-coordinate)
          while (u < w)
          { v = (u+w)/2;
            if (Y[i] > Vertex[t][v].y)
              u = v+1;
            else
              w = v;
          }
          withinbounds[t] = (N[t] == 0 || !outofbounds(X[i], Y[i], Edge[t][u]));
        }
        if (withinbounds[0] && withinbounds[1])
          printf("%d\n", i+1);
      }
      printf("0\n");
    }
  }
  return 0;
}
