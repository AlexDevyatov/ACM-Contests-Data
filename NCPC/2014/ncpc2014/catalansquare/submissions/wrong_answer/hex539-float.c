#include <stdio.h>

long double choose(long long a,long long b) {
    return a*b == b*b ? 1
         : b? a*choose(a-1,b-1)/b
         : 0;
}

int main(int argc, char **argv) {
    int n; scanf("%d", &n);
    printf("%.0Lf\n", choose(n*2+2,n+1)/(n+2));
    return 0;
}
