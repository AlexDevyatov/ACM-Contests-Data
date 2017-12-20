// Doubloon Game
// Solution by Thomas Beuman

#include <cstdio>
using namespace std;

int main()
{ int runs, run, S, K;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d\n", &S, &K);
    printf("%d\n", K % 2 == 0 && S % (K+1) == K ? K : (S % (K+1)) % 2);
  }
  return 0;
}
