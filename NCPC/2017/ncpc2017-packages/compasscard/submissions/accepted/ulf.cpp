#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
using namespace std;

typedef pair<int, int> pii;

multiset<pii> A[3];
vector<int> nA[3];
priority_queue<pii> Q;

struct card {
	int a[3];
	int id, u;
	bool in_deck;
};

int uniqueness(card c) {
	int sum = 0;
	for (int i = 0; i < 3; ++i) {
		multiset<pii>::iterator next, same;
		int angle;
		if (nA[i][c.a[i]] > 1)
			continue;
		next = A[i].upper_bound(pii(c.a[i], c.id));
		if (next == A[i].end())
			angle = A[i].begin()->first + 360;
		else
			angle = next->first;
		same = A[i].lower_bound(pii(c.a[i], c.id));
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
	map<int, card> C;
	for (int j = 0; j < 3; ++j)
		nA[j] = vector<int>(360, 0);
	for (int i = 0; i < n; ++i) {
		card c;
		cin >> c.a[0] >> c.a[1] >> c.a[2] >> c.id;
		c.in_deck = true;
		for (int j = 0; j < 3; ++j) {
			A[j].insert(pii(c.a[j],c.id));
			nA[j][c.a[j]]++;
		}
		C[c.id] = c;
	}
	for (map<int, card>::iterator it = C.begin(); it != C.end(); ++it) {
		it->second.u = uniqueness(it->second);
		Q.push(pii(-it->second.u, it->second.id));
	}
	int cards_left = n;
	while (true) {
		pii p = Q.top();
		Q.pop();
		card &c = C[p.second];
		if (c.in_deck && p.first == -c.u) {
			cards_left--;
			cout << c.id << endl;
			if (!cards_left)
				break;
			c.in_deck = false;
			for (int i = 0; i < 3; ++i) {
				A[i].erase(A[i].lower_bound(pii(c.a[i], c.id)));
				nA[i][c.a[i]] -= 1;
			}
			for (int i = 0; i < 3; ++i) {
				multiset<pii>::iterator it = A[i].lower_bound(pii(c.a[i], -1));
				if (nA[i][c.a[i]] == 1) {
					int u = it->second;
					C[u].u = uniqueness(C[u]);
					Q.push(pii(-C[u].u, C[u].id));
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
					Q.push(pii(-C[u1].u, C[u1].id));
					C[u2].u = uniqueness(C[u2]);
					Q.push(pii(-C[u2].u, C[u2].id));
				}
			}
		}
	}
}