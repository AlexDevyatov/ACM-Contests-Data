// In and Out
// Solution in O(NR) by Thomas Beuman

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int INF = 9999999; // "Infinity"

bool Sentry[1101];
int Road[10000][3];
int Twin[1101];
int Length[1101][1101];

int Dis[1101];
int Pred[1101]; // Predecessor in shortest path
int Edge[20100][3];

// Finds shortest path in the presence of negative edges
int bellmanford (int N, int start, int finish)
{ int i, j, k, r, d, R = 0;
  // Construct list of edges
  for (i = 1; i <= N; i++)
    for (j = 1; j <= N; j++)
      if (Length[i][j] < INF)
      { Edge[R][0] = i;
        Edge[R][1] = j;
        Edge[R][2] = Length[i][j];
        R++;
      }
  memset(Dis, 63, sizeof(Dis)); // Initialize to "infinity"
  Dis[start] = 0;
  // Relax all edges N-1 times
  for (k = 0; k < N-1; k++)
    for (r = 0; r < R; r++)
    { i = Edge[r][0];
      j = Edge[r][1];
      d = Edge[r][2];
      if (Dis[i] + d < Dis[j])
      { Dis[j] = Dis[i] + d;
        Pred[j] = i;
      }
    }
  return Dis[finish];
}

int main()
{ int runs, run, N, R, S, Boat, GovH, r, s, a, b, a2, b2, i, j, d;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &N, &R);
    Boat = 1;
    GovH = N;
    for (r = 0; r < R; r++)
      scanf("%d %d %d\n", &Road[r][0], &Road[r][1], &Road[r][2]);
    scanf("%d\n", &S);
    memset(Sentry, false, sizeof(Sentry));
    memset(Length, 63, sizeof(Length));
    // For all nodes with a sentry: create a twin node (the original is for incoming edges, the twin is for outgoing edges)
    for (s = 1; s <= S; s++)
    { scanf("%d", &j);
      N++; // Add new node to the back
      Twin[j] = N;
      Sentry[j] = Sentry[N] = true; // Label both as having a sentry
      Length[j][N] = 0; // Directed edge from original node to twin
    }
    for (r = 0; r < R; r++)
    { a = Road[r][0];
      b = Road[r][1];
      a2 = (Sentry[a] ? Twin[a] : a); // Node for outgoing edges
      b2 = (Sentry[b] ? Twin[b] : b);
      Length[a2][b] = Length[b2][a] = min(Length[a2][b], Road[r][2]); // Ignore/overwrite longer roads
    }
    d = bellmanford(N, Boat, GovH);
    // For the edges used: reverse the directions (for sentries only) and negate the lengths
    for (j = GovH; j != Boat; j = i)
    { i = Pred[j]; // Edge i->j was used
      Length[j][i] = -Length[i][j];
      if (Sentry[i] || Sentry[j])
        Length[i][j] = INF; // Do not pass sentry twice
    }
    d += bellmanford(N, Boat, GovH); // Find shortest path again and add to previous result
    if (d < INF)
      printf("%d\n", d);
    else
      printf("No safe route\n");
  }
  return 0;
}
