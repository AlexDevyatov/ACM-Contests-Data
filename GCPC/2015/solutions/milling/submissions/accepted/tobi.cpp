#include <iostream>
#include <algorithm>

using namespace std;
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
int W, S, X, Y, Ws[10000][100], M[100], tmp;

int main() {
	cin >> W >> S >> X >> Y;
	FOR(i, 0, W) FOR(j, 0, X) cin >> Ws[i][j];
	FOR(i, 0, S) FOR(j, 0, X) {
		cin >> tmp;
		M[j] = max(M[j], tmp);
	}
	FOR(i, 0, W) {
		FOR(j, 0, X) {
			Ws[i][j] = min(Ws[i][j], Y-M[j]);
			if (j != 0) cout << " ";
			cout << Ws[i][j];
		}
		cout << endl;
	}

	return 0;
}
