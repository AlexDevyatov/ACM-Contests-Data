#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const double eps = 1e-7;

class point
{ public:
  double x, y;
  point() {}
  point (double x0, double y0)
  { x = x0;  y = y0;
  }
};

class vctr
{ public:
  double dx, dy;
  vctr() {}
  vctr (double dx0, double dy0)
  { dx = dx0;  dy = dy0;
  }
};

class linesegment
{ public:
  double x1, y1, x2, y2;
  linesegment() {}
  linesegment (double x1a, double y1a, double x2a, double y2a)
  { x1 = x1a;  y1 = y1a;  x2 = x2a;  y2 = y2a;
  }
  vctr normal()
  { double n = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return vctr((y1-y2)/n, (x2-x1)/n);
  }
};

class ABCeqn // a*t^2 + b*t + c
{ public:
  double a, b, c;
  ABCeqn() {}
  ABCeqn (double a0, double b0, double c0)
  { a = a0;  b = b0;  c = c0;
  }
  int roots (double& t1, double& t2) // Returns number of roots
  { if (fabs(a) < eps)
    { if (fabs(b) < eps)
        return 0;
      t1 = -c/b;
      return 1;
    }
    double d = b*b - 4*a*c;
    if (d < -eps)
      return 0;
    if (d < eps)
    { t1 = -b / (2*a);
      return 1;
    }
    t1 = (-b - sqrt(d)) / (2*a);
    t2 = (-b + sqrt(d)) / (2*a);
    return 2;
  }
};

int X[20], Y[20];
point Vertex[20];
linesegment Edge[20];
vector<point> Possible_solutions;

ABCeqn operator - (ABCeqn eq1, ABCeqn eq2)
{ return ABCeqn(eq1.a-eq2.a, eq1.b-eq2.b, eq1.c-eq2.c);
}

void add_possible_solutions (ABCeqn equation, vctr direction, point point_on_line)
{ double root1 = 0, root2 = 0;
  int n = equation.roots(root1, root2);
  if (n > 0)
    Possible_solutions.push_back(point(point_on_line.x + direction.dx * root1, point_on_line.y + direction.dy * root1));
  if (n > 1)
    Possible_solutions.push_back(point(point_on_line.x + direction.dx * root2, point_on_line.y + direction.dy * root2));
}

// Distance to line (squared) as a function of t
ABCeqn dis_to_line (linesegment s, vctr direction, point point_on_line)
{ ABCeqn equation;
  vctr ns = s.normal();
  // dis^2 = [(point_on_line.x + direction.dx * t - s.x1) * ns.dx + (point_on_line.y + direction.dy * t - s.y1) * ns.dy] ^ 2
  double p = direction.dx*ns.dx + direction.dy*ns.dy;
  double q = (point_on_line.x-s.x1)*ns.dx + (point_on_line.y-s.y1)*ns.dy;
  return ABCeqn(p*p, 2*p*q, q*q);
}

// Distance to vertex (squared) as a function of t
ABCeqn dis_to_vertex (point p, vctr direction, point point_on_line)
{ ABCeqn equation;
  // dis^2 = (point_on_line.x + direction.dx * t - p.x)^2 + (point_on_line.y + direction.dy * t - p.y)^2
  equation.a = direction.dx*direction.dx + direction.dy*direction.dy;
  equation.b = 2*direction.dx*(point_on_line.x-p.x) + 2*direction.dy*(point_on_line.y-p.y);
  equation.c = (point_on_line.x-p.x)*(point_on_line.x-p.x) + (point_on_line.y-p.y)*(point_on_line.y-p.y);
  return equation;
}

// Bisector of two lines (as point_on_line + direction * t)
void bisector (linesegment s, linesegment t, vctr& direction, point& point_on_line)
{ vctr ns = s.normal(), nt = t.normal();
  // The distance of (x,y) to line s is ns.dx * x + ns.dy * y - ns.dx * s.x1 - ns.dy * s.y1
  // The distance of (x,y) to line t is nt.dx * x + nt.dy * y - nt.dx * s.x1 - nt.dy * s.y1
  double a = ns.dx - nt.dx, b = ns.dy - nt.dy;
  double c = s.x1 * ns.dx + s.y1 * ns.dy - t.x1 * nt.dx - t.y1 * nt.dy;
  // The bisector is ax + by = c
  direction = vctr(-b, a);
  if (fabs(a) + fabs(b) < eps) // Parallel line segments
    return;
  if (fabs(a) > fabs(b))
    point_on_line = point(c/a, 0);
  else
    point_on_line = point(0, c/b);
}

// Perpendicular bisector of two vertices (as point_on_line + direction * t)
void perp_bisector (point p, point q, vctr& direction, point& point_on_line)
{ direction = vctr(p.y - q.y, q.x - p.x);
  point_on_line = point((p.x + q.x) / 2, (p.y + q.y) / 2);
}

// Returns if p is inside the polygon
bool inside (point p, int N)
{ int i;
  bool in = false;
  // Draw an imaginary vertical half-line from p and count the number of times it crosses the perimeter of the polygon
  for (i = 0; i < N; i++)
  { linesegment s = Edge[i];
    double dx1 = p.x + eps - s.x1, dx2 = p.x + eps - s.x2;
    double area = p.x*s.y1 - p.y*s.x1 + s.x1*s.y2 - s.y1*s.x2 + s.x2*p.y - s.y2*p.x; // Is negative for clockwise orientation
    if (dx1 * dx2 < 0 && dx1 * area < 0) // s1 and s2 on opposite sides of the line and intersection is above p
      in = !in;
  }
  return in;
}

// Distance between a point and a linesegment
double dis (point p, linesegment s)
{ double dx12 = s.x2 - s.x1, dy12 = s.y2 - s.y1;
  double dx1p = p.x - s.x1, dy1p = p.y - s.y1;
  double dx2p = p.x - s.x2, dy2p = p.y - s.y2;
  if (dx12*dx1p + dy12*dy1p < 0) // Angle p-s1-s2 larger than 90 deg
    return sqrt(dx1p*dx1p + dy1p*dy1p); // Distance to vertex 1
  else if (-dx12*dx2p - dy12*dy2p < 0) // Angle p-s2-s1 larger than 90 deg
    return sqrt(dx2p*dx2p + dy2p*dy2p); // Distance to vertex 2
  else
    return fabs(dx12*dy1p - dy12*dx1p) / sqrt(dx12*dx12 + dy12*dy12); // Distance to line
}

int main()
{ int runs, run, N, i, j, k, s;
  double r, maxr;
  vctr direction;
  point point_on_line, p;
  ABCeqn equation1, equation2;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d\n", &N);
    for (i = 0; i < N; i++)
      scanf("%d %d\n", &X[i], &Y[i]);
    for (i = 0; i < N; i++)
    { Vertex[i] = point(X[i], Y[i]);
      Edge[i] = linesegment(X[i], Y[i], X[(i+1)%N], Y[(i+1)%N]);
    }
    Possible_solutions.clear();
    // All pairs of vertices
    for (i = 0; i < N; i++)
      for (j = i+1; j < N; j++)
      { perp_bisector(Vertex[i], Vertex[j], direction, point_on_line);
        equation1 = dis_to_vertex(Vertex[i], direction, point_on_line);
        // Together with another vertex
        for (k = j+1; k < N; k++)
        { equation2 = dis_to_vertex(Vertex[k], direction, point_on_line);
          add_possible_solutions(equation1 - equation2, direction, point_on_line);
        }
        // Together with an edge
        for (k = 0; k < N; k++)
        { equation2 = dis_to_line(Edge[k], direction, point_on_line);
          add_possible_solutions(equation1 - equation2, direction, point_on_line);
        }
      }
    // All pairs of edges
    for (i = 0; i < N; i++)
      for (j = i+1; j < N; j++)
      { bisector(Edge[i], Edge[j], direction, point_on_line);
        if (fabs(direction.dx) + fabs(direction.dy) < eps) // Parallel line segments
          continue;
        equation1 = dis_to_line(Edge[i], direction, point_on_line);
        // Together with another edge
        for (k = j+1; k < N; k++)
        { equation2 = dis_to_line(Edge[k], direction, point_on_line);
          add_possible_solutions(equation1 - equation2, direction, point_on_line);
        }
        // Together with a vertex
        for (k = 0; k < N; k++)
        { equation2 = dis_to_vertex(Vertex[k], direction, point_on_line);
          add_possible_solutions(equation1 - equation2, direction, point_on_line);
        }
      }
    maxr = 0;
    for (s = Possible_solutions.size() - 1; s >= 0; s--)
    { p = Possible_solutions[s];
      if (inside(p, N)) // point inside polygon
      { r = 1e9;
        for (i = 0; i < N; i++)
          r = min(r, dis(p, Edge[i]));
        maxr = max(maxr, r);
      }
    }
    printf("%.10lf\n", maxr);
  }
  return 0;
}









