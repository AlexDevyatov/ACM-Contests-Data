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

#define M_PI       3.14159265358979323846

using namespace std;

struct Circle {
	int x, y, r;
};

struct Interval {
	double a, b;

	bool operator<(const Interval& r) const {
		return (b < r.b);
	}
	bool contains(double ang) {
		if (a < b) return (a <= ang && ang <= b);
		else return (a <= ang || ang <= b);
	}
};

int N;
Circle C[1005];
Interval I[1005];
double L[2010];

void checkInput() {
	for (int i = 0; i < N; i++) {
		if (C[i].x < -10000 || C[i].x > 10000 || C[i].y < -10000 || C[i].y > 10000 || C[i].r < 1 || C[i].r > 10000) {
			cout << "Bad coordinates of circle " << i << endl;
		}
		for (int j = i+1; j < N; j++) {
			if ((C[i].x - C[j].x) * (C[i].x - C[j].x) + (C[i].y - C[j].y) * (C[i].y - C[j].y) < (C[i].r + C[j].r) * (C[i].r + C[j].r)) {
				cout << "Circles " << i << " and " << j << " intersect" << endl;
			}
		}
		if (C[i].x * C[i].x + C[i].y * C[i].y <= C[i].r * C[i].r) {
			cout << "Circle " << i << " hits origin" << endl;
		}
	}

	for (int i = 0; i < N; i++) {
		double mid = atan2((double)C[i].y, (double)C[i].x);
		double dA = asin((double)C[i].r / sqrt((double)(C[i].x * C[i].x + C[i].y * C[i].y)));
		L[2*i] = mid - dA;
		if (L[2*i] < -M_PI) L[2*i] += 2.0 * M_PI;
		L[2*i+1] = mid + dA;
		if (L[2*i+1] >= M_PI) L[2*i+1] -= 2.0 * M_PI;
	}

	sort(L, L+2*N);

	double error = 2.0 * M_PI;
	for (int i = 1; i < 2 * N; i++) {
		error = min(error, L[i] - L[i-1]);
	}
	error = min(error, L[0] - L[2*N-1] + 2.0 * M_PI);

	if (error < 0.000001) {
		cout << "Error is too small" << endl;
	}
}

void onerun() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> C[i].x >> C[i].y >> C[i].r;

	checkInput();

	for (int i = 0; i < N; i++) {
		double mid = atan2((double)C[i].y, (double)C[i].x);
		double dA = asin((double)C[i].r / sqrt((double)(C[i].x * C[i].x + C[i].y * C[i].y)));
		I[i].a = mid - dA;
		if (I[i].a < -M_PI) I[i].a += 2.0 * M_PI;
		I[i].b = mid + dA;
		if (I[i].b >= M_PI) I[i].b -= 2.0 * M_PI;
	}

	sort(I, I+N);

	int opt = N;
	for (int i = 0; i < N; i++) {
		int cur = 1;
		double last = I[i].b;
		for (int j = (i+1)%N; j != i; j = (j+1)%N) {
			if (!I[j].contains(last)) {
				cur++; last = I[j].b;
			}
		}
		opt = min(cur, opt);
	}

	cout << opt << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}
