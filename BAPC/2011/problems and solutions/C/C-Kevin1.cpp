#include <stdlib.h>
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

#define EPSILON 0.000001

typedef long long int lli;

using namespace std;

struct Island {
	lli x, y;
};

int N, M, K, M1, M2;
Island I[500005];

struct View {
	lli i1, i2;
	double a, b;
	bool operator<(const View& r) const {
		if (a == r.a) return (b < r.b);
		else return (a < r.a);
	}
};

View V1[10005];
View V2[10005];

void onerun() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> I[i].x >> I[i].y;
	cin >> K;

	for (int cases = 0; cases < K; cases++) {
		cin >> M;
		M1 = 0; M2 = 0;
		for (int i = 0; i < M; i++) {
			int i1, i2;
			cin >> i1 >> i2; i1--; i2--;
			double a = (double)(I[i2].y - I[i1].y) / (double)(I[i2].x - I[i1].x);
			double b = (double)(a * I[i1].x - I[i1].y);
			if (I[i1].x < I[i2].x) {
				V1[M1].i1 = i1; V1[M1].i2 = i2; V1[M1].a = a; V1[M1].b = b; M1++;
			}
			else {
				V2[M2].i1 = i1; V2[M2].i2 = i2; V2[M2].a = a; V2[M2].b = b; M2++;
			}
		}
		
		sort(V1, V1+M1);
		sort(V2, V2+M2);

		vector<View> S1;
		if (M1 > 0) S1.push_back(V1[0]); 
		if (M1 > 1) S1.push_back(V1[1]);
		int z = 2;
		// lower hull
		for (int i = 2; i < M1; i++) {
			while (z >= 2 && (S1[z-1].a - S1[z-2].a) * (V1[i].b - S1[z-1].b) - (S1[z-1].b - S1[z-2].b) * (V1[i].a - S1[z-1].a) > 0) {
				S1.pop_back(); z--;
			}
			S1.push_back(V1[i]); z++;
		}

		vector<View> S2;
		if (M2 > 0) S2.push_back(V2[0]);
		if (M2 > 1) S2.push_back(V2[1]);
		z = 2;
		// upper hull
		for (int i = 2; i < M2; i++) {
			while (z >= 2 && (S2[z-1].a - S2[z-2].a) * (V2[i].b - S2[z-1].b) - (S2[z-1].b - S2[z-2].b) * (V2[i].a - S2[z-1].a) < 0) {
				S2.pop_back(); z--;
			}
			S2.push_back(V2[i]); z++;
		}		

		for (int i = 0; i < N; i++) {
			double A = (double)I[i].x, B = -(double)I[i].y; // L = Ax + B
			// check upper hull
			if (S2.size() > 0) {
				int x = -1;
				int y = S2.size() - 1;
				while (x + 1 < y) {
					int h = (x+y)/2;
					if (S2[h+1].b - S2[h].b <= A * (S2[h+1].a - S2[h].a)) x = h;
					else y = h;
				}
				if (S2[y].a * A + B >= S2[y].b - EPSILON || S2[y].i1 == i || S2[y].i2 == i) continue;
			}

			// check lower hull
			if (S1.size() > 0) {
				int x = -1;
				int y = S1.size() - 1;
				while (x + 1 < y) {
					int h = (x+y)/2;
					if (S1[h+1].b - S1[h].b >= A * (S1[h+1].a - S1[h].a)) x = h;
					else y = h;
				}
				if (S1[y].a * A + B <= S1[y].b + EPSILON || S1[y].i1 == i || S1[y].i2 == i) continue;
			}
			cout << (i+1) << endl;
		}
		cout << "0" << endl;
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}
