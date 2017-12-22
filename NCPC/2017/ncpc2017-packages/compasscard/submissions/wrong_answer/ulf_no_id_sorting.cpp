#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

multiset<pii> A[3];
vector<int> nA[3];
priority_queue<pii> Q;

struct card {
	int a[3];
	int id, i, u;
	bool in_deck;
};

int uniqueness(card c) {
	int sum = 0;
	for (int i = 0; i < 3; ++i) {
		multiset<pii>::iterator next, same;
		int angle;
		if (nA[i][c.a[i]] > 1)
			continue;
		next = A[i].upper_bound(pii(c.a[i], c.i));
		if (next == A[i].end())
			angle = A[i].begin()->first + 360;
		else
			angle = next->first;
		same = A[i].lower_bound(pii(c.a[i], c.i));
		if (same == A[i].begin()) {
			angle -= (--A[i].end())->first - 360;
		} else {
			int d = (--same)->first;
			angle -= d;
		}
		sum += angle;
	}
	return sum;
}

int main() {
	int n;
	cin >> n;
	vector<card> C(n);
	for (int j = 0; j < 3; ++j)
		nA[j] = vector<int>(360, 0);
	for (int i = 0; i < n; ++i) {
		cin >> C[i].a[0] >> C[i].a[1] >> C[i].a[2] >> C[i].id;
		C[i].i = i;
		C[i].in_deck = true;
		for (int j = 0; j < 3; ++j) {
			A[j].insert(pii(C[i].a[j],i));
			nA[j][C[i].a[j]]++;
		}
	}
	for (int i = 0; i < n; ++i) {
		C[i].u = uniqueness(C[i]);
		Q.push(pii(-C[i].u, i));
	}
	int cards_left = n;
	while (true) {
		pii p = Q.top();
		Q.pop();
		card &c = C[p.second];
		if (c.in_deck && p.first == -c.u) {
			cout << C[p.second].id << endl;
			cards_left--;
			if (!cards_left)
				break;
			c.in_deck = false;
			for (int i = 0; i < 3; ++i) {
				A[i].erase(A[i].lower_bound(pii(c.a[i], c.i)));
				nA[i][c.a[i]] -= 1;
			}
			for (int i = 0; i < 3; ++i) {
				multiset<pii>::iterator it = A[i].lower_bound(pii(c.a[i], -1));
				if (nA[i][c.a[i]] == 1) {
					int u = it->second;
					C[u].u = uniqueness(C[u]);
					Q.push(pii(-C[u].u, C[u].i));
				} else if (nA[i][c.a[i]] == 0) {
					int u1, u2;

					if (it == A[i].end())
						u2 = A[i].begin()->second;
					else
						u2 = it->second;
					if (it == A[i].begin())
						u1 = (--A[i].end())->second;
					else if (A[i].size() > 1)
						u1 = (--it)->second;
					C[u1].u = uniqueness(C[u1]);
					Q.push(pii(-C[u1].u, C[u1].i));
					C[u2].u = uniqueness(C[u2]);
					Q.push(pii(-C[u2].u, C[u2].i));
				}
			}
		}
	}
}