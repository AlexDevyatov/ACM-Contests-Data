#include <stdlib.h>
#include <cstdio>
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

using namespace std;

int N;

void compute(int A1, int A2, int B1, int B2, int C1, int C2, int D1, int D2, int k) {
	int A = A2 - A1 + 1;
	int B = B2 - B1 + 1;
	int C = C2 - C1 + 1;
	int D = D2 - D1 + 1;
	int q = 1;
	for (int i = 0; i < k; i++) q *= 3;

	if (k == 0) {
		if (B > 0) printf("Ninja %d is a heavy pirate\n", B1);
		else printf("Ninja %d is a light pirate\n", C1);
		return;
	}

	string s;

	if (A <= 0 && B <= 1 && C <= 1) { // B + C <= 3
		if (B >= C) {
			if (B >= 2) {
				printf("%d + %d\n", B1, B1 + 1); fflush(NULL);
				cin >> s;
				if (s[0] == 'L') compute(0, -1, B1, B1, 0, -1, 0, -1, k - 1);
				else if (s[0] == 'R') compute(0, -1, B1+1, B1+1, 0, -1, 0, -1, k - 1);
				else compute(0, -1, B1+2, B2, C1, C2, 0, -1, k - 1);
			}
			else if (B == 1) {
				printf("%d + %d\n", B1, D1); fflush(NULL);
				cin >> s;
				if (s[0] == 'L') compute(0, -1, B1, B1, 0, -1, D1, D2, k - 1);
				else compute(0, -1, 0, -1, C1, C2, D1, D2, k - 1);
			}
		}
		else {
			if (C >= 2) {
				printf("%d + %d\n", C1, C1 + 1); fflush(NULL);
				cin >> s;
				if (s[0] == 'L') compute(0, -1, 0, -1, C1+1, C1+1, 0, -1, k - 1);
				else if (s[0] == 'R') compute(0, -1, 0, -1, C1, C1, 0, -1, k - 1);
				else compute(0, -1, B1, B2, C1+2, C2, 0, -1, k - 1);
			}
			else if (C == 1) {
				printf("%d + %d\n", C1, D1); fflush(NULL);
				cin >> s;
				if (s[0] == 'R') compute(0, -1, 0, -1, C1, C1, D1, D2, k - 1);
				else compute(0, -1, B1, B2, 0, -1, D1, D2, k - 1);
			}
		}
		return;
	}

	if (D <= 0 && B <= 0 && C <= 0) { // starting case
		int x = min(A/2, (q/3 - 1)/2);
		printf("%d-%d + %d-%d\n", A1, A1 + x - 1, A1 + x, A1 + 2 * x - 1); fflush(NULL);
		cin >> s;
		if (s[0] == 'L') {
			compute(0, -1, A1, A1 + x - 1, A1 + x, A1 + 2 * x - 1, A1 + 2 * x, N, k - 1);
		}
		else if (s[0] == 'R') {
			compute(0, -1, A1 + x, A1 + 2 * x - 1, A1, A1 + x - 1, A1 + 2 * x, N, k - 1);
		}
		else {
			compute(A1 + 2 * x, N, 0, -1, 0, -1, 1, A1 + 2 * x - 1, k - 1);
		}
	}
	else if (B <= 0 && C <= 0) {
		int x = min(q/3, A);
		printf("%d-%d + %d-%d\n", A1, A1 + x - 1, D1, D1 + x - 1); fflush(NULL);
		cin >> s;
		if (s[0] == 'L') {
			compute(0, -1, A1, A1 + x - 1, 0, -1, D1, D2, k - 1);
		}
		else if (s[0] == 'R') {
			compute(0, -1, 0, -1, A1, A1 + x - 1, D1, D2, k - 1);
		}
		else {
			compute(A1 + x, N, 0, -1, 0, -1, D1, D2, k - 1);
		}
	}
	else {	// Hard case: B + C <= q
		if (B >= C) {
			if (B/2 <= q/3) {
				int x = B/2;
				int y = min(C/2, q/3 - x);
				if (y > 0) printf("%d-%d %d-%d + %d-%d %d-%d\n", B1, B1 + x - 1, C1, C1 + y - 1, B1 + x, B1 + 2 * x - 1, C1 + y, C1 + 2 * y - 1);
				else printf("%d-%d + %d-%d\n", B1, B1 + x - 1, B1 + x, B1 + 2 * x - 1);
				fflush(NULL);
				cin >> s;
				if (s[0] == 'L') {
					compute(0, -1, B1, B1 + x - 1, C1 + y, C1 + 2 * y - 1, C1 + 2 * y, C2, k - 1);
				}
				else if (s[0] == 'R') {
					compute(0, -1, B1 + x, B1 + 2 * x - 1, C1, C1 + y - 1, C1 + 2 * y, C2, k - 1);
				}
				else {
					compute(0, -1, B1 + 2 * x, B2, C1 + 2 * y, C2, B1, B1 + 2 * x - 1, k - 1);
				}
			}
			else {
				printf("%d-%d + %d-%d\n", B1, B1 + q/3 - 1, B1 + q/3, B1 + 2 * q/3 - 1); fflush(NULL);
				cin >> s;
				if (s[0] == 'L') {
					compute(0, -1, B1, B1 + q/3 - 1, 0, -1, B1 + q/3, B2, k - 1);
				}
				else if (s[0] == 'R') {
					compute(0, -1, B1 + q/3, B1 + 2 * q/3 - 1, 0, -1, B1, B1 + q/3 - 1, k - 1);
				}
				else {
					compute(0, -1, B1 + 2 * q/3, B2, C1, C2, B1, B1 + 2 * q/3 - 1, k - 1);
				}
			}
		}
		else {
			if (C/2 <= q/3) {
				int x = C/2;
				int y = min(B/2, q/3 - x);
				if (y > 0) printf("%d-%d %d-%d + %d-%d %d-%d\n", C1, C1 + x - 1, B1, B1 + y - 1, C1 + x, C1 + 2 * x - 1, B1 + y, B1 + 2 * y - 1);
				else printf("%d-%d + %d-%d\n", C1, C1 + x - 1, C1 + x, C1 + 2 * x - 1);
				fflush(NULL);
				cin >> s;
				if (s[0] == 'L') {
					compute(0, -1, B1, B1 + y - 1, C1 + x, C1 + 2 * x - 1, B1 + 2 * y, B2, k - 1);
				}
				else if (s[0] == 'R') {
					compute(0, -1, B1 + y, B1 + 2 * y - 1, C1, C1 + x - 1, B1 + 2 * y, B2, k - 1);
				}
				else {
					compute(0, -1, B1 + 2 * y, B2, C1 + 2 * x, C2, C1, C1 + 2 * x - 1, k - 1);
				}
			}
			else {
				printf("%d-%d + %d-%d\n", C1, C1 + q/3 - 1, C1 + q/3, C1 + 2 * q/3 - 1); fflush(NULL);
				cin >> s;
				if (s[0] == 'L') {
					compute(0, -1, 0, -1, C1 + q/3, C1 + 2 * q/3 - 1, C1, C1 + q/3 - 1, k - 1);
				}
				else if (s[0] == 'R') {
					compute(0, -1, 0, -1, C1, C1 + q/3 - 1, C1 + q/3, C2, k - 1);
				}
				else {
					compute(0, -1, B1, B2, C1 + 2 * q/3, C2, C1, C1 + 2 * q/3 - 1, k - 1);
				}
			}
		}
	}
}

void onerun() {
	cin >> N;
	int k = 0;
	int q = 1;
	while (2 * N + 3 > q) {
		k++; q *= 3;
	}
	compute(1, N, 0, -1, 0, -1, 0, -1, k);
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}