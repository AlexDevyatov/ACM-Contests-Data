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

typedef long long int lli;

using namespace std;

struct Pirate {
	lli t[4];
	lli arrive;
	int side;
	bool operator<(const Pirate& r) const {
		if (arrive == r.arrive) {
			if (side == 0) return (t[3] < r.t[3]);
			else return (t[1] < r.t[1]);
		}
		else return (arrive > r.arrive);
	}
};

int N, K;
Pirate P[1005];
priority_queue<Pirate> Q1, Q2;

void onerun() {
	cin >> N >> K;
	while (!Q1.empty()) Q1.pop();
	while (!Q2.empty()) Q2.pop();
	for (int i = 0; i < K; i++) {
		cin >> P[i].t[0] >> P[i].t[1] >> P[i].t[2] >> P[i].t[3];
		P[i].arrive = i - K; P[i].side = 0;
		Q1.push(P[i]);
	}

	lli T = 0;

	while (!Q1.empty() || !Q2.empty()) {
		if (Q2.empty()) {
			Pirate p = Q1.top(); Q1.pop();
			if (N > 0) {
				T = max(p.arrive, T) + p.t[0];
				p.side = 1; p.arrive = T + p.t[1]; Q2.push(p); N--;
			}
		}
		else if (Q1.empty()) {
			Pirate p = Q2.top(); Q2.pop();
			T = max(p.arrive, T) + p.t[2];
			if (N > 0) {
				p.side = 0; p.arrive = T + p.t[3]; Q1.push(p);
			}
		}
		else {
			Pirate p1 = Q1.top();
			Pirate p2 = Q2.top();
			if (p2.arrive <= T || p2.arrive <= p1.arrive) {
				Q2.pop();
				T = max(p2.arrive, T) + p2.t[2];
				if (N > 0) {
					p2.side = 0; p2.arrive = T + p2.t[3]; Q1.push(p2);
				}
			}
			else {
				Q1.pop();
				if (N > 0) {
					T = max(p1.arrive, T) + p1.t[0];
					p1.side = 1; p1.arrive = T + p1.t[1]; Q2.push(p1); N--;
				}
			}
		}
	}

	cout << T << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}