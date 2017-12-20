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

int N, S, P;
int F[100005];

void onerun() {
	cin >> S >> N >> P;
	F[0] = 0;
	F[1] = 1;
	for (int k = 2; k <= S; k++) {
		int count = 0;
		F[k] = 0;
		for (int i = 1; i <= min(k, N); i++) {
			if (F[k-i] == 0 || F[k-i] == i) {
				count++; F[k] = i;
			}
		}
		if (count >= 2) F[k] = -1;
	}

	if (F[S] == P) F[S] = 0;
	if (F[S] != -1) cout << F[S] << endl;
	else {
		for (int i = 1; i <= min(S, N); i++) {
			if (i == P) continue;
			if (F[S-i] == 0 || F[S-i] == i) {
				cout << i << endl;
				break;
			}
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