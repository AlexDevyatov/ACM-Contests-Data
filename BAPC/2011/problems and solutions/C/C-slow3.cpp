#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>
#include <time.h>

#define BLOCKS 64

typedef double lli;
//typedef long long int lli;

using namespace std;

struct Island {
	lli x, y;
	int ID;
	bool operator<(const Island& r) const {
		return (ID < r.ID);
	}
};

struct Block {
	vector<Island> L;
	lli minX, minY, maxX, maxY;
	bool good;
};

int N, M, K;
Island I[500005];
bool good[500005];
Block B[BLOCKS][BLOCKS];


void onerun() {
	scanf("%d", &N);
	lli maxX = 0, maxY = 0;

	//clock_t start, mid, end;
	//start = clock() * CLK_TCK;

	for (int i = 0; i < N; i++) {
		scanf("%lf %lf", &I[i].x, &I[i].y);
		I[i].ID = i;
		maxX = max(maxX, I[i].x+1); maxY = max(maxY, I[i].y+1);
	}

	for (int i = 0; i < BLOCKS; i++) for (int j = 0; j < BLOCKS; j++) {
		B[i][j].L.clear();
		B[i][j].minX = maxX; B[i][j].minY = maxY; B[i][j].maxX = 0; B[i][j].maxY = 0;
	}

	for (int i = 0; i < N; i++) {
		int ix = (I[i].x * BLOCKS)/maxX;
		int iy = (I[i].y * BLOCKS)/maxY;
		B[ix][iy].L.push_back(I[i]);
		B[ix][iy].minX = min(B[ix][iy].minX, I[i].x);
		B[ix][iy].minY = min(B[ix][iy].minY, I[i].y);
		B[ix][iy].maxX = max(B[ix][iy].maxX, I[i].x);
		B[ix][iy].maxY = max(B[ix][iy].maxY, I[i].y);
	}

	//mid = clock() * CLK_TCK;

	scanf("%d", &K);

	for (int cases = 0; cases < K; cases++) {
		for (int i = 0; i < N; i++) good[i] = true;
		for (int x = 0; x < BLOCKS; x++) for (int y = 0; y < BLOCKS; y++) B[x][y].good = true;

		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			int i1, i2;
			scanf("%d %d", &i1, &i2); i1--; i2--;
			lli LA = I[i2].y - I[i1].y;
			lli LB = I[i1].x - I[i2].x;
			lli LC = LA * I[i1].x + LB * I[i1].y;
			for (int x = 0; x < BLOCKS; x++) for (int y = 0; y < BLOCKS; y++) {
				if (!B[x][y].good) continue;
				lli minC = min(LA * B[x][y].minX, LA * B[x][y].maxX) + min(LB * B[x][y].minY, LB * B[x][y].maxY);
				lli maxC = max(LA * B[x][y].minX, LA * B[x][y].maxX) + max(LB * B[x][y].minY, LB * B[x][y].maxY);
				if (minC > LC) continue;
				if (maxC <= LC) {
					B[x][y].good = false; 
					for (vector<Island>::iterator it = B[x][y].L.begin(); it != B[x][y].L.end(); it++) good[it->ID] = false;
					continue;
				}
				for (vector<Island>::iterator it = B[x][y].L.begin(); it != B[x][y].L.end(); it++) {
					if (!good[it->ID]) continue;
					if (LA * it->x + LB * it->y <= LC) good[it->ID] = false;
				}
			}
		}

		for (int i = 0; i < N; i++) if (good[i]) printf("%d\n", i+1);

		printf("0\n");
	}

	//end = clock() * CLK_TCK;

	//printf("Time1 = %lf\nTime2 = %lf\n", 0.000001 * (mid - start), 0.000001 * (end - mid));
}

int main(int argc, char *argv[]) 
{
	int runs;
	scanf("%d", &runs);
	while(runs--) onerun();
	return 0;
}
