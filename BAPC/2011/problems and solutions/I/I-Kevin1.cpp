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

using namespace std;

typedef long long ll;

struct Pirate {
	ll center, len;
	bool cap;
	bool operator<(const Pirate& r) const {
		return (center < r.center);
	}
};

int N;
Pirate P[1005];
ll Q[1005][1005];

void onerun() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> P[i].center >> P[i].len;
		P[i].cap = (i == 0);
		if (i == 0 && P[i].len%2 == 1) P[i].len++;
		if (P[i].center < -1000000000 || P[i].center > 1000000000 || P[i].len < 1 || P[i].len > 1000000000) cout << "INVALID INPUT!" << endl;
	}

	sort(P, P+N);

	for (int i = 0; i < N - 1; i++) if (P[i].center == P[i+1].center) cout << "INVALID INPUT!" << endl;

	int capID = -1;
	for (int i = 1; i <= N; i++) if (P[i-1].cap) capID = i;

	for (int i = 0; i <= N; i++) {
		Q[i][0] = INT_MIN;
		if (i >= capID) Q[i][0] = INT_MAX;
		for (int j = i+1; j <= N; j++) Q[i][j] = INT_MAX;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			if (!P[i-1].cap) {
				Q[i][j] = Q[i-1][j];
				if (Q[i-1][j-1] <= P[i-1].center) {
					Q[i][j] = min(Q[i][j], max(P[i-1].center, Q[i-1][j-1] + P[i-1].len));
				}
			}
			else {
				if (Q[i-1][j-1] <= P[i-1].center - P[i-1].len/2) Q[i][j] = P[i-1].center + P[i-1].len/2;
				else Q[i][j] = INT_MAX;
			}
		}
	}

	for (int i = N; i >= 0; i--) {
		if (Q[N][i] < INT_MAX) {
			cout << i << endl;
			break;
		}
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}