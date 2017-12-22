#include <bits/stdc++.h>

/*

  19: 1+1097*2^7
  20:  257*1097      -> 137*2^11 -> 17*2^13 -> 2^16
  21: 1+17*2^15      -> 17*2^15  -> 2^18
  22:  17*65537      -> 2^20
  23: 1+17*137+2^10  -> 17*137*2^10 -> 17*2^16  -> 2^19
  24: 1+257^2*2^6    -> 257^2*2^6   -> 257*2^13 -> 2^20
  25: 137*65537      -> 17*2^19  -> 2^22
 */
typedef long long ll;
const int MAX = 1000000000;

std::vector<int> primes;

int main(void) {
  int *len = new int[MAX+1];
  int *phi = new int[MAX+1];
  int *facs1 = new int[MAX+1];
  int *facs2 = new int[MAX+1];
  int max_seen = 2;
  for (int n = 2; n <= MAX; ++n) phi[n] = n, facs1[n] = 0, facs2[n] = 0;
  for (int n = 2; n <= MAX; ++n) {
    if (phi[n] == n) {
      phi[n] = n-1;
      if (n > 2) facs2[n] = int(ceil(sqrt(n)));
      for (int m = 2*n; m <= MAX; m += n) {
	phi[m] = phi[m]/n*(n-1);
	facs2[m] = facs1[m];
	facs1[m] = n;
      }
    }
    len[n] = len[phi[n]]+facs2[n];
    if (len[n] >= max_seen) {
      max_seen = len[n];
      printf("%7d: %d", len[n], n);
      int nn = phi[n];
      while (1) {
	printf(" -> %d", nn);
	if (nn == 1) break;
	nn = phi[nn];
      }
      printf("\n");
      fflush(stdout);
    }
  }
}
