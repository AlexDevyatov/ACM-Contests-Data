#include <stdlib.h>
#include <vector>
#include <queue>
#include <set>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits.h>

typedef long long int lli;

using namespace std;

lli N, A, B, C, Y;
lli N2;

bool check(lli x, lli k) {
	lli k2 = (1 << k);
	lli x2 = (x * x)%k2;
	lli ax2 = (A * x2)%k2;
	lli bx = (B * x)%k2;
	return ((ax2 + bx + C)%k2 == 0);
}

void onerun() {
	cin >> Y >> A >> B >> C >> N;
	N2 = 1 << N;
	C = (C - Y + N2)%N2;

	if (A == 0 && B == 0 && C == 0) cout << "No unique solution" << endl;
	else {
		lli mul = 1;
		while (A%2 == 0 && B%2 == 0 && C%2 == 0) {
			A /= 2; B /= 2; C /= 2; mul *= 2;
		}	
		set<lli> L[32];
		if (C%2 == 0) L[0].insert(0);
		if ((A+B+C)%2 == 0) L[0].insert(1);
		for (int i = 1; i < N; i++) {
			if (L[i-1].size() == 0) break;
			for (set<lli>::iterator it = L[i-1].begin(); it != L[i-1].end(); it++) {
				if (check(*it, i+1)) L[i].insert(*it);
				if (check(*it + (1 << i), i+1)) L[i].insert(*it + (1 << i));
			}
		}
		if (L[N-1].size() != 1) cout << "No unique solution" << endl;
		else cout << (*L[N-1].begin()) << endl;
	}
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}
