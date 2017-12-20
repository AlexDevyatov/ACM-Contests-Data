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

void onerun() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> P[i].center >> P[i].len;
		P[i].cap = (i == 0);
		if (i == 0 && P[i].len%2 == 1) P[i].len++;
	}

	sort(P, P+N);

	int capID = -1;
	for (int i = 0; i < N; i++) if (P[i].cap) capID = i;

	int k = 0;
	int i = 0;
	int left = INT_MIN;
	int leftmost = INT_MAX;
	int leftIndex = -1;
	while (i < capID) {
		for (int j = i; j < capID; j++) {
			int end = max(P[j].center, left + P[j].len);
			if (end < leftmost) {
				leftmost = end;
				leftIndex = j;
			}
		}
		if (leftmost <= P[capID].center - P[capID].len/2) {
			k++; left = leftmost; leftmost = INT_MAX; i = leftIndex + 1;
			while (i < capID && P[i].center < left) i++;
		}
		else i = capID;
	}

	k++;

	left = P[capID].center + P[capID].len/2;
	i = capID + 1;
	while (i < N && P[i].center < left) i++;
	leftmost = INT_MAX;
	leftIndex = -1;
	while (i < N) {
		for (int j = i; j < N; j++) {
			int end = max(P[j].center, left + P[j].len);
			if (end < leftmost) {
				leftmost = end;
				leftIndex = j;
			}
		}
		k++; left = leftmost; leftmost = INT_MAX; i = leftIndex + 1;
		while (i < N && P[i].center < left) i++;
	}

	cout << k << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}