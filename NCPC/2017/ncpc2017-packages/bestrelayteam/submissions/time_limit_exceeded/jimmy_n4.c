#include <stdio.h>

#define MAX_N 500

int main() {
  int i,j,k,l,n, best[4];
  double tm, best_time = 999.99, t1[MAX_N], t2[MAX_N];
  char names[MAX_N][21];

  scanf("%d", &n);
  for(i=0;i<n;i++) scanf("%s %lf %lf", names[i], t1+i, t2+i);

  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      for(k=j+1;k<n;k++)
        for(l=k+1;l<n;l++) {
          tm = t1[i] + t2[j] + t2[k] + t2[l];
          if (tm < best_time && i != j && i != k && i != l) {
            best_time = tm;
            best[0] = i;
            best[1] = j;
            best[2] = k;
            best[3] = l;
          }
        }

  printf("%0.2lf\n", best_time);
  for(i=0;i<4;i++)
    printf("%s\n", names[best[i]]);

  return 0;
}
