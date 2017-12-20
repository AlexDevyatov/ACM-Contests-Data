// Dividing the Loot
// Solution by Thomas Beuman

#include <cstdio>
#include <algorithm>
using namespace std;

int V[1000]; // The values of the items

int main()
{ int runs, run, P, N, i, t;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &P, &N);
    for (i = 0; i < N; i++)
      scanf("%d", &V[i]);
    sort(V, V+N); // Sort all the values (in ascending order)
    t = 0;
    for (i = N - N/(P+1); i < N; i++) // Select the floor(N/(P+1)) most valuable items
      t += V[i];
    printf("%d\n", t);
  }
  return 0;
}
