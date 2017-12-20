#include <vector>
#include <iostream>

using namespace std;

#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int main() {
	int W, S, X, Y;
	cin >> W >> S >> X >> Y;
	vector<vector<int> > pieces(W, vector<int>(X));
	FOR(w, 0, W)
		FOR(x, 0, X)
			cin >> pieces[w][x];
	vector<vector<int> > cuts(S, vector<int>(X));
	FOR(s, 0, S)
		FOR(x, 0, X)
			cin >> cuts[s][x];
	FOR(s, 1, S)
		FOR(x, 0, X)
			cuts[0][x] = max(cuts[0][x], cuts[s][x]);
	FOR(w, 0, W)
		FOR(x, 0, X)
			cout << min(pieces[w][x], Y - cuts[0][x]) << ((x == X - 1)?"\n":" ");
	return 0;
}
