#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

long long x[128][2];
long double p;
int N;
int main() {
	cin >> p >> N;
	FOR(i,0,N)FOR(j,0,2)cin >> x[i][j];
	long long A = 0, PARTS = 0;
	FOR (i, 1, N + 1)
		A += x[i-1][0] * x[i%N][1] - x[i%N][0] * x[i-1][1];
	FOR(i,0,N)
		FOR(j,1,4)
			PARTS += x[(i+j-1)%N][0] * x[(i+(j%3))%N][1] -
					 x[(i+j-1)%N][1] * x[(i+(j%3))%N][0];
	printf("%.15Lf\n", sqrt(PARTS / ((1.0 - p) * A)));
	return 0;
}
