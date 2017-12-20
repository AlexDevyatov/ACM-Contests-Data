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

// rather slow implementation, should still work

using namespace std;

int N, D;
int Q[105];

int check(int k) {
	if (k == N) {
		for (int i = max(N - D, 0); i < N; i++) if (Q[i] == 1) return N+1;
		return 0;
	}
	int best = N+1;

	if (k - D < 0 || Q[k-D] == 0) best = min(best, check(k+1));
	if (k - D < 0 || Q[k-D] == 1) {
		for (int i = max(k - D, 0); i <= min(k+D, N-1); i++) Q[i] = 1 - Q[i];
		best = min(best, 1+check(k+1));
		for (int i = max(k - D, 0); i <= min(k+D, N-1); i++) Q[i] = 1 - Q[i];
	}
	return best;
}

void onerun() {
	cin >> N >> D;
	for (int i = 0; i < N; i++) {
		cin >> Q[i];
	}

	int R = check(0);
	if (R <= N) cout << R << endl;
	else cout << "impossible" << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}