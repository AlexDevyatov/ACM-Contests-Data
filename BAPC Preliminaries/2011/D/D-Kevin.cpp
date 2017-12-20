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

using namespace std;

vector<string> split(string s) {
	vector<string> L;
	size_t x = 0;
	while (true) {
		size_t x2 = s.find(' ', x);
		L.push_back(s.substr(x, x2 - x));
		if (x2 == string::npos) break;
		x = x2+1;
	}
	return L;
}

int Q[1005][1005];
int D[8][8];
bool matched[8];
vector<string> L1, L2;

int minErrors(int k) {
	if (k == L1.size()) return 0;
	int minE = INT_MAX;
	for (int i = 0; i < L2.size(); i++) {
		if (matched[i]) continue;
		matched[i] = true;
		minE = min(minE, D[k][i] + minErrors(k+1));
		matched[i] = false;
	}
	return minE;
}

void onerun() {
	string S1, S2;
	getline(cin, S2);
	getline(cin, S1);
	L2 = split(S2);
	L1 = split(S1);

	for (int i = 0; i < L1.size(); i++) {
		for (int j = 0; j < L2.size(); j++) {
			int N1 = L1[i].length(), N2 = L2[j].length();
			for (int x = 0; x <= N1; x++) Q[x][0] = x;
			for (int y = 0; y <= N2; y++) Q[0][y] = y;
			for (int x = 1; x <= N1; x++) {
				for (int y = 1; y <= N2; y++) {
					Q[x][y] = min(1 + min(Q[x-1][y], Q[x][y-1]), Q[x-1][y-1] + (L1[i][x-1] == L2[j][y-1] ? 0 : 1));
				}
			}
			D[i][j] = Q[N1][N2];
		}
	}

	for (int i = 0; i < L2.size(); i++) matched[i] = false;

	cout << minErrors(0) << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	string s;
	getline(cin, s);
	while(runs--) onerun();
	return 0;
}