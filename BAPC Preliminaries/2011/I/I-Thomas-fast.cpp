// In and Out
// Solution in O(R log R) by Thomas Beuman

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

const int INF = 9999999; // "Infinity"

bool Sentry[1101];
int Road[10000][3];
int Twin[1101];
int Length[1101][1101];

int Dis[1101];
int Pred[1101]; // Predecessor in shortest path
int Phi[1101]; // Node potentials
bool Seen[1101];
vector<int> Adj[1101]; // Adjacency list

struct node
{ int id, dis;
  node(int i, int d)
  { id = i;
    dis = d;
  }
};

bool operator< (const node& n1, const node& n2)
{ return n1.dis > n2.dis;
}

int dijkstra (int N, int start, int finish)
{ int i, j, d;
  unsigned int k;
  memset(Dis, 63, sizeof(Dis));
  Dis[start] = 0;
  memset(Seen, false, sizeof(Seen));
  priority_queue<node> pq;
  pq.push(node(start, 0));
  while (!pq.empty())
  { i = pq.top().id;
    d = pq.top().dis;
    pq.pop();
    if (Seen[i])
      continue;
    Seen[i] = true;
    for (k = 0; k < Adj[i].size(); k++)
    { j = Adj[i][k];
      if (!Seen[j] && Length[i][j] < INF && Dis[i] + Length[i][j] + Phi[i] - Phi[j] < Dis[j])
      { Dis[j] = Dis[i] + Length[i][j] + Phi[i] - Phi[j];
        Pred[j] = i;
        pq.push(node(j, Dis[j]));
      }
    }
  }
  return Dis[finish] + Phi[finish];
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
    for (i = 1; i <= N+S; i++)
      Adj[i].clear();
    // For all nodes with a sentry: create a twin node (the original is for incoming edges, the twin is for outgoing edges)
    for (s = 1; s <= S; s++)
    { scanf("%d", &j);
      N++; // Add new node to the back
      Twin[j] = N;
      Sentry[j] = Sentry[N] = true; // Label both as having a sentry
      Length[j][N] = 0; // Directed edge from original node to twin
      Adj[j].push_back(N);
    }
    for (r = 0; r < R; r++)
    { a = Road[r][0];
      b = Road[r][1];
      a2 = (Sentry[a] ? Twin[a] : a); // Node for outgoing edges
      b2 = (Sentry[b] ? Twin[b] : b);
      Length[a2][b] = Length[b2][a] = min(Length[a2][b], Road[r][2]); // Ignore/overwrite longer roads
      Adj[a2].push_back(b);
      Adj[b2].push_back(a);
    }
    memset(Phi, 0, sizeof(Phi));
    d = dijkstra(N, Boat, GovH);
    // For the edges used: reverse the directions (for sentries only) and negate the lengths
    for (j = GovH; j != Boat; j = i)
    { i = Pred[j]; // Edge i->j was used
      Length[j][i] = -Length[i][j];
      if (Sentry[i] || Sentry[j])
      { Adj[j].push_back(i); // Add edge in opposite direction
        Length[i][j] = INF; // Do not pass sentry twice
      }
    }
    memcpy(Phi, Dis, sizeof(Dis)); // Set node potentials
    d += dijkstra(N, Boat, GovH); // Find shortest path again and add to previous result
    if (d < INF)
      printf("%d\n", d);
    else
      printf("No safe route\n");
  }
  return 0;
}
