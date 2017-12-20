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

struct State {
	int top, right, front;
};

struct Move {
	int steps, dir;
};

State rollX(State s, int steps) {
	State r = s;
	steps = (steps > 0 ? steps%4 : 4-((-steps)%4));
	if (steps == 1) {
		r.top = 7 - s.right; r.right = s.top;	
	}
	if (steps == 2) {
		r.top = 7 - s.top; r.right = 7 - s.right;	
	}
	if (steps == 3) {
		r.top = s.right; r.right = 7 - s.top;	
	}
	return r;
}

State rollY(State s, int steps) {
	State r = s;
	steps = (steps > 0 ? steps%4 : 4-((-steps)%4));
	if (steps == 1) {
		r.top = s.front; r.front = 7 - s.top;	
	}
	if (steps == 2) {
		r.top = 7 - s.top; r.front = 7 - s.front;	
	}
	if (steps == 3) {
		r.top = 7 - s.front; r.front = s.top;	
	}
	return r;
}

vector<Move> L;

void onerun() {
	string s;
	cin >> s;
	if (s.length() > 1000) cout << "ERROR" << endl;

	L.clear();
	Move m; m.steps = 0;
	int i = 0, d = 1;
	while (s[i] != '.') {
		if (s[i] >= '0' && s[i] <= '9') m.steps = 10 * m.steps + (s[i] - '0');
		if (s[i] == 'X') {
			if (m.steps == 0) m.steps = d;
			else m.steps *= d;
			if (abs(m.steps) > 9999999) cout << "ERROR" << endl;
			m.dir = 0;
			L.push_back(m); m.steps = 0;
		}
		if (s[i] == 'Y') {
			if (m.steps == 0) m.steps = d;
			else m.steps *= d;
			if (abs(m.steps) > 9999999) cout << "ERROR" << endl;
			m.dir = 1;
			L.push_back(m); m.steps = 0;
		}
		if (s[i] == '-' || s[i] == '+') d *= -1;
		i++;
	}

	int x = 0, y = 0;
	State z; z.top = 1; z.right = 4; z.front = 2;
	for (int i = 0; i < L.size(); i++) {
		if (L[i].dir == 0) {
			x += L[i].steps; z = rollX(z, L[i].steps);
		}
		else {
			y += L[i].steps; z = rollY(z, L[i].steps);
		}
	}

	cout << "position (" << x << "," << y << "), " << z.top << " dots" << endl;
}

int main(int argc, char *argv[]) 
{
	int runs;
	cin >> runs;
	while(runs--) onerun();
	return 0;
}
