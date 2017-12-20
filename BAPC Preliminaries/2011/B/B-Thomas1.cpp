// RNG in Reverse
// Solution by Thomas Beuman

#include <cstdio>
using namespace std;

int main()
{ int runs, run, y, a, b, c, n, x, m;
  scanf("%d\n", &runs);
  for (run = 0; run < runs; run++)
  { scanf("%d %d %d %d %d\n", &y, &a, &b, &c, &n);
    // There is a unique solution if and only if...
    if ((a % 2 == 0 && b % 2 == 1) || (n == 1 && a == 1 && b == 0))
    { x = 0;
      for (m = 1; m <= n; m++) // Solve modulo 2^m
        if ((a*x*x+b*x+c-y) & ((1<<m)-1)) // If this value doesn't work...
          x ^= (1<<(m-1)); // ...it must be the other one
      printf("%d\n", x);
    }
    else
      printf("No unique solution\n");
  }
  return 0;
}









