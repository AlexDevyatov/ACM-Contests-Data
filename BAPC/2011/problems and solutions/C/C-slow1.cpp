#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

typedef double lli;

using namespace std;

struct Island {
	lli x, y;
};

int N, M, K;
Island I[500005];

struct View {
	lli dx, dy, D;
};

View V[2005];

void onerunNaive() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%lf %lf", &I[i].x, &I[i].y);
	scanf("%d", &K);

	for (int cases = 0; cases < K; cases++) {
		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			int i1, i2;
			scanf("%d %d", &i1, &i2); i1--; i2--;
			V[i].dx = I[i2].x - I[i1].x; V[i].dy = I[i2].y - I[i1].y;
			V[i].D = I[i2].x * I[i1].y - I[i1].x * I[i2].y;
		}

		for (int i = 0; i < N; ++i) {
			bool good = true;
			for (int j = 0; j < M; ++j) {
				if (I[i].y * V[j].dx - I[i].x * V[j].dy >= V[j].D) {
					good = false;
					break;
				}
			}
			if (good) printf("%d\n", i+1);
		}

		printf("0\n");
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	scanf("%d", &runs);
	while(runs--) onerunNaive();
	return 0;
}
