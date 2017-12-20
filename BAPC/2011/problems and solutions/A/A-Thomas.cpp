// Popping Balloons
// Solution by Thomas Beuman

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

const double pi = acos(-1);
const bool left = true, right = false;

struct tangent
{ int balloon;
  bool type; // Specifies whether the tangent touches the balloon on the left or on the right
  double angle;
  tangent() {}
  tangent (int b, bool t, double a)
  { balloon = b;  type = t;  angle = a;
  }
};

bool operator < (const tangent& t1, const tangent& t2)
{ return t1.angle < t2.angle;
}

tangent T[2000];
int Interval[1000];

int main()
{ int runs, run, n, i, j, x, y, r, start, s, best;
  double angle;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d\n", &n);
    if (n == 0) // Special case
    { printf("0\n");
      continue;
    }
    for (i = 0; i < n; i++)
    { scanf("%d %d %d\n", &x, &y, &r);
      // Compute the angles of the tangents
      for (j = 0; j < 2; j++)
      { angle = atan2(y, x) + (2*j-1) * asin(r / sqrt(x*x + y*y));
        if (angle < -pi || angle > pi) // Put the angle in the range [-pi, pi]
          angle += (angle < 0 ? 1 : -1) * 2*pi;
        T[2*i+j] = tangent(i, j ? left : right, angle);
      }
    }
    sort(T, T+2*n); // Sort all tangents by angle
    best = 9999;
    for (start = 0; start < 2*n; start++) // Select a tangent to start with (try all)
    { if (T[start].type == right) // Only use left tangents
        continue;
      memset(Interval, 0, sizeof(Interval));
      s = 1; // Number of shurikens needed
      i = start;
      // Make a full circle
      do
      { if (T[i].type == right) // New balloon in scope that needs popping
          Interval[T[i].balloon] = s;
        else if (Interval[T[i].balloon] == s) // Balloon about to get out of range: use shuriken
          s++;
        i = (i+1) % (2*n);
      }
      while (i != start);
      best = min(best, s);
    }
    printf("%d\n", best);
  }
  return 0;
}
