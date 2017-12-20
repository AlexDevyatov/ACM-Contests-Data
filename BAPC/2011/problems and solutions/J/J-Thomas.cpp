// Treasure Map
// Solution by Thomas Beuman

#include <cstdio>
#include <cmath>
using namespace std;

int main()
{ int runs, run, N, k;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d\n", &N);
    if (N % 4 == 2)
      printf("IMPOSSIBLE\n");
    else
    { for (k = (int)sqrt(N); N % k || (N/k-k) % 2; k--);
      printf("%d %d\n", (N/k-k)/2, (N/k+k)/2);
    }
  }
  return 0;
}
