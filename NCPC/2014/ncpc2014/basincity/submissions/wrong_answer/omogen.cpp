#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (int)b; ++i)
#define trav(it, v) for(auto it = v.begin(); it != v.end(); ++it)
#define all(x) x.begin(), x.end()

typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;

static vector<vector<int> > ed;
static int K, N;

static ll iterations = 0;
static vector<int> used;

ll cutoff = 100000000000;

void rec(int ind, int left, int above) {
	if (!left) throw true;
	if (iterations++ > cutoff) throw false;
	if (ind == N) return;
	if (above < left) return;
	if (!used[ind]) above--;
	if (!used[ind]) {
		int above2 = above;
		for (int j : ed[ind]) {
			if (j > ind && !used[j]) above2--;
			used[j]++;
		}
		rec(ind+1, left-1, above2);
		for (int j : ed[ind])
			used[j]--;
		if (above2 == above)
			return;
	}
	rec(ind+1, left, above);
}


bool solve() {
    cin >> K >> N;
	if (N >= K * 5 - 4)
		return true;
	used.assign(N, 0);
	ed.resize(N);
	vector<int> perm(N);
	for (int i = 0; i < N; ++i)
		perm[i] = i;
	random_shuffle(perm.begin(), perm.end());
	for (int i = 0; i < N; ++i) {
		int d;
		cin >> d;
		for (int j = 0; j < d; ++j) {
			int a;
			cin >> a;
			--a;
			ed[perm[i]].push_back(perm[a]);
		}
	}
	try {
		rec(0, K, N);
		return false;
	} catch(bool result) {
		return result;
	}
}

int main() {
    cin.sync_with_stdio(false);
    if (!solve())
		cout << "im";
	cout << "possible" << endl;
}
